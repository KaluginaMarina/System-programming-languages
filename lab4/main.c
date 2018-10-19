#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "higher_order.h"


/**
 * Функция для вывода list'а через пробелы
 * @param x
 */
void fun(int x) {
    printf("%d ", x);
}
/**
 * Функция для вывода list'а через переносы строки
 * @param x
 */
void fun1(int x){
    printf("%d\n", x);
}

int main() {
    int e;
//    printf("Введите элементы списка:\n");
//    struct list *list = NULL;
//    while (scanf("%d", &e) != EOF){
//        list_add_back(&list, e);
//    }
//
//    print_list(list);
//
//    printf("\n\nЭлемент #3:\n%d", list_get(list, 3));
//
//    printf("\n\nОчистили список:");
//    list_free(&list);
//    print_list(list);

    struct list *list = NULL;
    FILE *f = fopen("input.txt", "r");
    while ( fscanf(f, "%d", &e) != EOF) {
        list_add_back(&list, e);
    }


    print_list(list);
    printf("\n\nЭлемент #3:\n%d", list_get(list, 3));

    printf("\n\nВыведем список foreach'eм через пробел:");
    void (*pf)(int) = &fun;
    foreach(list, pf);
    printf("\n\nИ через перевод строки:\n");
    pf = &fun1;
    foreach(list, pf);


    printf("\n\nОчистили список:");
    list_free(&list);
    print_list(list);
    return 0;
}