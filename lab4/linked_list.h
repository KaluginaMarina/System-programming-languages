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
struct list* list_create(int e);

/**
 *  Функция для добавления элемента в начало списка
 *  Если список пуст, создает новый список
 *  @param list - указатель на список, в который добавляем элеент
 *  @return указатель на список
 */
struct list* list_add_front(struct list* list, int e);

/**
 *  Функция для добавления элемента в конец списка
 *  Если список пуст, создает новый список
 *  @param list - указатель на список, в который добавляем элеент
 *  @return указатель на список
 */
struct list* list_add_back(struct list* list, int e);

/**
 *  Функция для вывода всех эдементов списка на экран
 *  @param list - указатель на список
 */
 void print_list(struct list* list);

#endif //LAB4_LINKED_LIST_H
