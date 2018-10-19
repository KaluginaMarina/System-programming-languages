#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


int main() {
    int e;
    printf("Введите элементы списка:\n");
    struct list *list = NULL;
    while (scanf("%d", &e) != EOF){
        list_add_back(&list, e);
    }

    print_list(list);

    printf("\n\nЭлемент #3:\n%d", list_get(list, 3));

    printf("\n\nОчистили список:");
    list_free(&list);
    print_list(list);
//
//    FILE *f = fopen("input.txt", "r");
//    while ( fscanf(f, "%d", &e) != EOF) {
//        printf("%d ", e);
//    }
    return 0;
}