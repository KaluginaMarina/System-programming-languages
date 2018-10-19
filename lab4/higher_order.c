#include <stdio.h>
#include <stdlib.h>
#include "higher_order.h"

void foreach(struct list const* list, void (*f)(int)){
    while (list != NULL){
        f(list->elem);
        list = list->last;
    }
}

struct list* map(struct list const* list, int (*f)(int)){
    struct list* result_list = NULL;
    while (list != NULL){
        list_add_front(&result_list, f(list->elem));
        list = list->last;
    }
    return result_list;
}

int foldl(int acc, int (*f)(int, int), struct list const* list){
    while (list != NULL){
        acc = f(acc, list->elem);
        list = list->last;
    }
    return acc;
}

void map_mut(struct list* list, int (*f)(int)){
    while(list != NULL){
        list->elem = f(list->elem);
        list = list->last;
    }
}

struct list* iterator(int s, size_t n, int (*f)(int)){
    struct list* list = NULL;
    size_t i = 0;
    for(; i < n; ++i){
        list_add_front(&list, s);
        s = f(s);
    }
    return list;
}