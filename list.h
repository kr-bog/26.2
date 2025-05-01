#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;  //Указатель на следующий узел в списке
    struct Node* prev;  //Указатель на предыдущий узел в списке
} Node;

typedef struct List {
    Node* current;    //Указатель на текущий узел в списке
} List;

List* create_list();
List* copy_list(List* original);
void insert_after_current(List* list, int value);
void insert_before_current(List* list, int value);
void delete_current(List* list);
void move_next(List* list);
void move_prev(List* list);
void print_list(List* list);
void free_list(List* list);

#endif //LIST_H