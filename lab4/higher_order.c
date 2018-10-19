#include <stdio.h>
#include <stdlib.h>
#include "higher_order.h"

void foreach(struct list* list, void (*f)(int)){
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