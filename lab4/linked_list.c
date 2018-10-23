#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

struct list * list_create(int e) {
    struct list *new_elem_list = (struct list*)malloc(sizeof(struct list));
    new_elem_list->elem = e;
    new_elem_list->last = NULL;
    new_elem_list->next = NULL;
    return new_elem_list;
}

void list_add_front(struct list** list, int e){
    if (*list == NULL){
        *list = list_create(e);
        return;
    }
    struct list *new_elem_list = (struct list*)malloc(sizeof(struct list));
    new_elem_list->elem = e;
    new_elem_list->last = NULL;
    struct list* tmp_list = *list;
    while(tmp_list->last != NULL){
        tmp_list = tmp_list->last;
    }
    new_elem_list->next = tmp_list;
    tmp_list->last = new_elem_list;
}

void list_add_back(struct list** list, int e){
    if (*list == NULL){
        *list = list_create(e);
        return;
    }
    struct list *new_elem_list = (struct list*)malloc(sizeof(struct list));
    new_elem_list->elem = e;
    new_elem_list->next = NULL;
    new_elem_list->last = *list;
    (*list)->next = new_elem_list;
    *list = new_elem_list;
}

void print_list(struct list const* list){
    printf("\n===============================\nКоличество элементов: %lu\n", list_length(list));
    printf("Сумма элементов: %d\n", list_sum(list));
    if (list == NULL){
        printf("list слишком пуст\n===============================\n");
        return;
    }
    printf("list: ");
    while (list != NULL){
        printf("%d ", list->elem);
        list = list->last;
    }
    printf("\n===============================\n");
}

struct list* list_node_at(struct list const* list, unsigned int index){
    unsigned int i = 0;
    if (list == NULL){
        return NULL;
    }
    while (list->last != NULL){
        list = list->last;
    }
    while (i != index){
        ++i;
        list = list->next;
        if (list == NULL) {
            return NULL;
        }
    }
    return list;
}

void list_free(struct list** list){
    while (*list != NULL) {
        struct list* last = (*list)->last;
        free(*list);
        (*list) = last;
    }
}

size_t list_length(struct list const* list){
    size_t i = 0;
    while (list != NULL) {
        struct list* last = list->last;
        list = last;
        ++i;
    }
    return i;
}

int list_get(struct list const* list, unsigned int index){
    struct list* ret = list_node_at(list, index);
    return ret == NULL ? 0 : ret->elem;
}

int list_sum(struct list const* list){
    int sum = 0;
    while (list != NULL){
        sum += list->elem;
        list = list->last;
    }
    return sum;
}

bool load(struct list** list, const char* filename){
    int e;
    FILE* input_file = fopen(filename, "r");
    if (input_file == NULL) {
        return false;
    }
    while ( fscanf(input_file, "%d", &e) != EOF) {
        list_add_back(list, e);
    }
    fclose(input_file);
    return true;
}

bool save(struct list* list, const char* filename){
    FILE* output_file = fopen(filename, "w+");
    if (output_file == NULL){
        return false;
    }
    while (list != NULL) {
        fprintf(output_file, "%d ", list->elem);
        list = list->last;
    }
    fclose(output_file);
    return true;
}

bool serialize(struct list* list, const char* filename){
    FILE* output_file = fopen(filename, "w+");
    if (output_file == NULL){
        return false;
    }
    size_t sz = list_length(list), i;
    int* buf = (int*)malloc(sz* sizeof(int));
    for (i = 0; i < sz; ++i){
        *(buf + i) = list->elem;
        list = list->last;
    }
    fwrite(buf, sz, sizeof(int), output_file);
    fclose(output_file);
    return true;
}

bool deserialize(struct list** list, const char* filename){
    FILE* input_file = fopen(filename, "r");
    if (input_file == NULL) {
        return false;
    }
    fseek(input_file, 0, SEEK_END);
    long sz = ftell(input_file), i;
    rewind(input_file);

    int* buf = (int*)malloc(sz* sizeof(int));
    fread(buf, sz/sizeof(int), sizeof(int), input_file);

    for(i = 0; i < sz/ sizeof(int); ++i){
        list_add_front(list, *(buf + i));
    }
    fclose(input_file);
    return true;
}