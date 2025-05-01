#include <stdio.h>
#include <stdlib.h>
#include <accctrl.h>
#include "list.h"

#define MAX_LISTS 10 //максимальное количество списков

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    List* lists[MAX_LISTS] = {NULL};
    int active = -1;
    int id = 0;

    while (1) {
        printf("\n--- Меню ---\n");
        printf("1. Создать новый список\n");
        printf("2. Скопировать активный список\n");
        printf("3. Выбрать активный список\n");
        printf("4. Вставить после текущего\n");
        printf("5. Вставить перед текущим\n");
        printf("6. Удалить текущий элемент\n");
        printf("7. Следующий элемент\n");
        printf("8. Предыдущий элемент\n");
        printf("9. Печать активного списка\n");
        printf("10. Печать всех списков\n");
        printf("0. Выход\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:                             //создание нового списка
                if (id < MAX_LISTS) {
                    lists[id] = create_list();  // Создаем пустой список
                    active = id;                // Делаем его активным
                    printf("Создан список #%d\n", id++);
                }
                break;
            case 2:                             //коптирование списка
                if (active >= 0 && id < MAX_LISTS) {
                    lists[id] = copy_list(lists[active]);   // создаем копию
                    printf("Создана копия списка #%d как список #%d\n", active, id);
                    active = id++;
                }
                break;
            case 3:                             //выбор списка
                printf("Введите номер списка: ");
                int select;
                scanf("%d", &select);
                if (select >= 0 && select < id && lists[select]) {
                    active = select;
                }
                break;
            case 4:                             // Вставка после текущего элемента
                if (active >= 0) {
                    printf("Введите значение: ");
                    int v;
                    scanf("%d", &v);
                    insert_after_current(lists[active], v);
                }
                break;
            case 5:                             //вставка перед текущим элементом
                if (active >= 0) {
                    printf("Введите значение: ");
                    int v;
                    scanf("%d", &v);
                    insert_before_current(lists[active], v);
                }
                break;
            case 6:                             // Удаление текущего элемента
                if (active >= 0) delete_current(lists[active]);
                break;
            case 7:                             // Переход к следующему элементу
                if (active >= 0) move_next(lists[active]);
                break;
            case 8:                             // Переход к предыдущему элементу
                if (active >= 0) move_prev(lists[active]);
                break;
            case 9:                             // Печать активного списка
                if (active >= 0) {
                    printf("Список #%d: ", active);
                    print_list(lists[active]);
                }
                break;
            case 10:                          // Печать всех списков
                for (int i = 0; i < id; i++) {
                    if (lists[i]) {
                        printf("Список #%d: ", i);
                        print_list(lists[i]);
                    }
                }
                break;
            case 0:                          // Выход из программы
                for (int i = 0; i < id; i++) {
                    if (lists[i]) free_list(lists[i]);
                }
                return 0;
        }
    }
}
