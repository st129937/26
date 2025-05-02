#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* current;
    int exists;
} List;

//Ввод элементов списка
int* input_node(int len);

//Связь элемента со следующим и предыдцщим элементами списка
Node* create_node(int data);

//Поиск следующего наибольшего номера
int find_next_id(List lists[]);

//Создание пустого списка
void create_empty_node(List lists[], int id);

//Копирует список с выбранным номером
void copy_list(List lists[], int from_id, int to_id);

//Меняет список, с которым работает пользователь, на выбранный номер
void switch_active_list(List lists[], int* active_list_id, int new_id);

//Вставляет элемент после текущего
void insert_after(List lists[], int active_list_id);

//Вставляет элемент перед текущим
void insert_before(List lists[], int active_list_id);

//Удаляет текущий элемент
void delete_current(List lists[], int active_list_id);

//Переходит на предыдущий элемент
void go_forward(List lists[], int active_list_id);

//Переходит на следующи элемент
void go_back(List lists[], int active_list_id);

//Вывести все элементы
void print_all_lists(List lists[], int active_list_id);

//Очистка памяти
void free_all_lists(List lists[]);

#endif