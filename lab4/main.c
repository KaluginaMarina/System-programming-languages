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
    printf("0 -- %d\n", list_get(list, 0));
    printf("1 -- %d\n", list_get(list, 1));
    printf("5 -- %d\n", list_get(list, 5));
    printf("6 -- %d\n", list_get(list, 6));
    list_free(&list);
    print_list(list);
    list = list_add_back(list, 3);
    list = list_add_back(list, 4);
    list = list_add_front(list, 2);
    list = list_add_front(list, 1);
    print_list(list);
    return 0;
}