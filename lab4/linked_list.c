#include <stdlib.h>
#include "linked_list.h"

struct list * list_create(int e) {
    struct list *struct_list = malloc(sizeof(struct_list));
    struct_list->elem = e;
    struct_list->last = NULL;
    struct_list->next = NULL;
    return struct_list;
}