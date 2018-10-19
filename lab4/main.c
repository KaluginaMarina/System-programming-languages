#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "higher_order.h"


/**
 * Функция для вывода list'а через пробелы
 * @param x
 */
void fun_print_with_space(int x) {
    printf("%d ", x);
}

/**
 * Функция для вывода list'а через переносы строки
 * @param x
 */
void fun_print_with_n(int x){
    printf("%d\n", x);
}

/**
 * функция возводит в квадрат
 * @param x
 * @return x*x
 */
int fun_square(int x){
    return x*x;
}

/**
 * Функция возводит в куб
 * @param x
 * @return x*x
 */
int fun_cube(int x){
    return x*x*x;
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

    struct list* list = NULL;
    FILE *f = fopen("input.txt", "r");
    while ( fscanf(f, "%d", &e) != EOF) {
        list_add_back(&list, e);
    }

    printf("Считали с файла list.\n");
    print_list(list);
    printf("\n\nЭлемент #3:\n%d", list_get(list, 3));

    printf("\n\nВыведем список foreach'eм через перевод строки:\n");
    void (*pf)(int) = &fun_print_with_n;
    foreach(list, pf);
    printf("\n\nИ через перевод пробел:\n");
    pf = &fun_print_with_space;
    foreach(list, pf);

    printf("\n\nВозведем каждый элемент list'a в квадрат с помошью map:\n");
    int (*ipf)(int) = &fun_square;
    struct list* res_list = map(list, ipf);
    foreach(res_list, pf);

    printf("\n\nВозведем каждый элемент list'a в куб с помошью map:\n");
    ipf = &fun_cube;
    res_list = map(list, ipf);
    foreach(res_list, pf);


    printf("\n\nОчистили список:");
    list_free(&list);
    print_list(list);
    return 0;
}