#include <stdbool.h>
#include "allocation.h"
#include "sys/mman.h"

void* init(size_t init_size){
    if(init_size < sizeof(header))
        return NULL;

    HEAP_START = mmap(NULL, init_size,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);

    if(HEAP_START == MAP_FAILED)
        return NULL;

    header header_p;
    header_p.next = NULL;
    header_p.capacity = init_size;
    header_p.is_free = true;

    *(header*)HEAP_START = header_p;
}

void* _malloc(size_t query){
    if(query < MIN_BLOCK_SIZE){
        query = MIN_BLOCK_SIZE;
    }

    header* block = (header*)HEAP_START;

    while (true){
        if (block->is_free && query < block->capacity - sizeof(header) - MIN_BLOCK_SIZE){  //если в блок можно положить больше, чем 1 блок...
            //т.к мы пользуемся не всем блоком, остаток запишем в new и сделаем из него новый блок.
            size_t temp_size = block->capacity - query - sizeof(header);   //сколько осталось места
            header* new = (header*)((void*)block + block->capacity);      //новый блок находится сразу после того, который мы сейчас займем
            *new = *block;                                                //кинем header в начале new, а потом поменяем его capacity
            new->capacity = temp_size;
            block->capacity = query + sizeof(header);
            block->is_free = false;
            block->next = (void*)new;
            void* place = (void*)block + sizeof(header);                   // возвращаем указатель на паметь после heder'а
            return place;
        }

        if (!block->next){                                                 //если у нас нет следующего блока - создадим его
            void* p = mmap((void*)block + block->capacity, query,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED,-1,0); // попробуем выделить память для остатка, если не получится
            if(p == MAP_FAILED) {
                p = mmap(NULL, query,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
                if(p == MAP_FAILED)
                    return NULL;
            }
            //создадим header для этого блока
            header header_p;
            header_p.next = NULL;
            header_p.capacity = query;
            header_p.is_free = false;
            *(header*)p = header_p;
            block->next = p;
            return p + sizeof(header_p);
        }

        block = (header*)block->next;
    }

}

void* _free(void* p){
    //сейчас у нас указатель на данные, а надо на header
    p -= sizeof(header);
    header* head = (header*)p;
    head->is_free = true; //помечаем текущий блок пустым
    header* cur = (void*)head+head->capacity; //указатель на следующий элемент
    while(cur->is_free){    //надо объединить все пустые блоки, которые находятся после того, что мы очистили в один
        head->capacity += cur->capacity;       //увеличиваем размер блока
        cur = (void*)head + head->capacity;    //указатель на следующий блок
    }

}