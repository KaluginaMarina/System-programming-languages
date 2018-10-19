#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

int main() {

    printf("Введите элементы списка:\n");
    int e;
    struct list *list = NULL;
    while (scanf("%d", &e) != EOF){
        list = list_add_back(list, e);
    }
    print_list(list);

    printf("\n\nЭлемент #3:\n%d", list_get(list, 3));

    printf("\n\nОчистили список:");
    list_free(&list);
    print_list(list);

    return 0;
}