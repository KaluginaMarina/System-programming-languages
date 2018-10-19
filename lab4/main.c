#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "linked_list.h"
#include "higher_order.h"


/**
 * Функция для вывода list'а через пробелы
 */
void fun_print_with_space(int x) {
    printf("%d ", x);
}

/**
 * Функция для вывода list'а через переносы строки
 */
void fun_print_with_n(int x){
    printf("%d\n", x);
}

/**
 * функция возводит в квадрат
 */
int fun_square(int x){
    return x*x;
}

/**
 * Функция возводит в куб
 */
int fun_cube(int x){
    return x*x*x;
}

/**
 * Функция возввращает сумму элементов
 */
int fun_sum(int acc, int x){
    return acc + x;
}

/**
 * Функция для поиска максимального значения в list
 */
int fun_max(int acc, int x){
    return acc > x ? acc : x;
}

/**
 * Функция для поиска минимального в list
 */
int fun_min(int acc, int x){
    return acc < x ? acc : x;
}

/**
 * Функция возвращает модуль числа
 */
int fun_abs(int x){
    return abs(x);
}

/**
 * Функция для степент 2
 */
int fun_pow_two(int x){
    return x*2;
}

int main() {
    int e;

    struct list* list = NULL;

    printf("Введите - 1 для считывания с файла\n"
           "        - 2 для считывания с stdin\n");

    int k;
    scanf("%d", &k);
    switch (k){
        case 1: {
            load(&list, "input.txt");
            printf("Считали с файла list.\n");
            break;
        }
        case 2: {
            while (scanf("%d", &e) != EOF){
                list_add_back(&list, e);
            }
            break;
        }
        default: {
            printf("Неверно.");
            return 0;
        }
    }
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
    list_free(&res_list);

    int (*ipfii)(int, int) = &fun_sum;
    printf("\n\nСумма элементов, посчитанная с помощью foldl: %d\n", foldl(0, ipfii, list));
    ipfii = &fun_max;
    printf("Максимальный элемент в list (с помошью foldl): %d\n", foldl(INT_MIN, ipfii, list));
    ipfii = &fun_min;
    printf("Минимальный элемент в list (с помошью foldl): %d\n", foldl(INT_MAX, ipfii, list));

    printf("\n\nМодуль всех чисел, с помошью map_mut:\n");
    int (*ipfi)(int) = &fun_abs;
    map_mut(list, ipfi);
    foreach(list, pf);

    printf("\n\n10 первых степеней двойки:\n");
    ipfi = &fun_pow_two;
    res_list = iterator(1, 10, ipfi);
    foreach(res_list, pf);
    list_free(&res_list);


    save(list, "output.txt");
    printf("\n\nКонечный list можно найти в output.txt\n");

    serialize(list, "ser");
    list_free(&list);
    deserialize(&list, "ser");
    printf("\nПосле сериализации:");
    print_list(list);


    printf("\nОчистили список:");
    list_free(&list);
    print_list(list);
    return 0;
}