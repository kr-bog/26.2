#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Создание нового пустого списка
List* create_list() {
    return (List*)calloc(1, sizeof(List));
}

// Вставка нового элемента после текущего
void insert_after_current(List* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node)); // создаем новый узед
    new_node->data = value;                       //заполняем данные

    //если список пуст
    if (!list->current) {
        new_node->next = new_node->prev = new_node; // делаем узел сам на себя
        list->current = new_node;
        return;
    }
    // Если список не пуст
    Node* curr = list->current; //текущий узел
    Node* next = curr->next;   //следующий

    //Обновляем узлы
    curr->next = new_node;  //текущий указывает на новый
    new_node->prev = curr;  //новый на текущий
    new_node->next = next;  //новый на следующий
    next->prev = new_node;  //следующий на новый
}

//вствка перед текущим
void insert_before_current(List* list, int value) {
    move_prev(list);                    //Предыдущий становится текущим
    insert_after_current(list, value);  //вставляем после нового текщего
}

//удаление текущего элемента
void delete_current(List* list) {
    if (!list->current) return;

    Node* to_delete = list->current;    //узел для удаления

    //если это единственный элемент в списке
    if (to_delete->next == to_delete) {
        free(to_delete);        //освобождаем память
        list->current = NULL;   //список пуст
        return;
    }

    //если несколько элементов
    Node* prev = to_delete->prev;   //предыдущий узел
    Node* next = to_delete->next;   //следующий узел

    prev->next = next;  //предыдущий указывает на сл
    next->prev = prev;

    list->current = next;   //следующий узел - текущий
    free(to_delete);
}

//переход к следующему элементу
void move_next(List* list) {
    if (list->current) list->current = list->current->next;
}

//переход к предыдущему
void move_prev(List* list) {
    if (list->current) list->current = list->current->prev;
}

//список
void print_list(List* list) {
    if (!list->current) {
        printf("[пусто]\n");
        return;
    }

    Node* start = list->current;
    Node* node = start;

    do {
        printf(node == list->current ? "[%d] " : "%d ", node->data);
        node = node->next;
    } while (node != start);

    printf("\n");
}

//копировать список
List* copy_list(List* original) {
    if (!original || !original->current) return create_list();

    List* copy = create_list();
    Node* start = original->current;
    Node* node = start;

    int index = 0;
    int curr_index = 0;
    Node* temp = original->current;

    while (temp->prev != original->current) {
        curr_index++;
        temp = temp->prev;
    }

    // Копируем элементы
    do {
        insert_after_current(copy, node->data);
        move_next(copy);
        node = node->next;
        index++;
    } while (node != start);

    for (int i = 0; i < index - curr_index; i++) {
        move_prev(copy);
    }

    return copy;
}

//освобождаем список
void free_list(List* list) {
    if (!list || !list->current) {
        free(list);
        return;
    }

    Node* start = list->current;
    Node* node = start->next;

    while (node != start) {
        Node* tmp = node;
        node = node->next;
        free(tmp);
    }

    free(start);
    free(list);
}
