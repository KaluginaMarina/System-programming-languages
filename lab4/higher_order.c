#include <stdio.h>
#include <stdlib.h>
#include "higher_order.h"

void foreach(struct list* list, void (*f)(int)){
    while (list != NULL){
        f(list->elem);
        list = list->last;
    }
}