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

struct list* list_add_front(struct list* list, int e){
    if (list == NULL){
        return list_create(e);
    }
    struct list *new_elem_list = (struct list*)malloc(sizeof(struct list));
    new_elem_list->elem = e;
    new_elem_list->last = NULL;
    struct list* tmp_list = list;
    while(tmp_list->last != NULL){
        tmp_list = tmp_list->last;
    }
    new_elem_list->next = tmp_list;
    tmp_list->last = new_elem_list;
    return list;
}

struct list* list_add_back(struct list* list, int e){
    if (list == NULL){
        return list_create(e);
    }
    struct list *new_elem_list = (struct list*)malloc(sizeof(struct list));
    new_elem_list->elem = e;
    new_elem_list->next = NULL;
    new_elem_list->last = list;
    list->next = new_elem_list;
    return new_elem_list;
}

void print_list(struct list* list){
    printf("\n===============================\nКоличество элементов: %d\n", list_length(list));
    if (list == NULL){
        printf("list слишком пуст");
        return;
    }
    while (list->last != NULL){
        list = list->last;
    }
    printf("list: ");
    while (list != NULL){
        printf("%d ", list->elem);
        list = list->next;
    }
    printf("\n===============================\n");
}

struct list* list_get(struct list* list, int index){
    int i = 0;
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

int list_length(struct list* list){
    int i = 0;
    while (list != NULL) {
        struct list* last = list->last;
        list = last;
        ++i;
    }
    return i;
}