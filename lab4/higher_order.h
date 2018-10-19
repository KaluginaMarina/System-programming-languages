#include "linked_list.h"

#ifndef LAB4_HIGHER_ORDER_H
#define LAB4_HIGHER_ORDER_H

/**
 *  функция по очереди выполняет функцию на всех элементах саиска по порядку
 *  @param list - указатель на list элементов
 *  @param f - указатель на функцию
 */
void foreach(struct list* list, void (*f)(int));

/**
 * Функция создает новый список, в котором к содержимомоу каждому элементу list'а применяется функция f
 * @param list - указатель на исходный список (список не изменяется)
 * @param f - указатель на функцию
 * @return новый list с результатом приминения f к каждому элементу list'a
 */
struct list* map(struct list const* list, int (*f)(int));
#endif //LAB4_HIGHER_ORDER_H
