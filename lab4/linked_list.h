#ifndef LAB4_LINKED_LIST_H
#define LAB4_LINKED_LIST_H


/**
 *  Структура связного списка
 *  Элементом списка является integer
 *  В структуре хранятся указатели на следующий и предыдущий элемент3
 */
struct list {
    int elem;
    struct list* next;
    struct list* last;
};

/**
 *  Функция для создания списка с первым элементом
 *  @param e - элемент списка
 *  @return указатель на список
 */
struct list * list_create(int e);


#endif //LAB4_LINKED_LIST_H
