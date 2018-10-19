#include "linked_list.h"

#ifndef LAB4_HIGHER_ORDER_H
#define LAB4_HIGHER_ORDER_H

/**
 *  функция по очереди выполняет функцию на всех элементах саиска по порядку
 */
void foreach(struct list* list, void (*f)(int));

#endif //LAB4_HIGHER_ORDER_H
