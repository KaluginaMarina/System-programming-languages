#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
    struct list* list = list_create(2);
    list = list_add_front(list, 1);
    list = list_add_front(list, 0);
    list = list_add_back(list, 4);
    list = list_add_back(list, 5);
    list = list_add_front(list, -1);
    print_list(list);
    return 0;
}