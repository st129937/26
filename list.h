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

//���� ��������� ������
int* input_node(int len);

//����� �������� �� ��������� � ���������� ���������� ������
Node* create_node(int data);

//����� ���������� ����������� ������
int find_next_id(List lists[]);

//�������� ������� ������
void create_empty_node(List lists[], int id);

//�������� ������ � ��������� �������
void copy_list(List lists[], int from_id, int to_id);

//������ ������, � ������� �������� ������������, �� ��������� �����
void switch_active_list(List lists[], int* active_list_id, int new_id);

//��������� ������� ����� ��������
void insert_after(List lists[], int active_list_id);

//��������� ������� ����� �������
void insert_before(List lists[], int active_list_id);

//������� ������� �������
void delete_current(List lists[], int active_list_id);

//��������� �� ���������� �������
void go_forward(List lists[], int active_list_id);

//��������� �� �������� �������
void go_back(List lists[], int active_list_id);

//������� ��� ��������
void print_all_lists(List lists[], int active_list_id);

//������� ������
void free_all_lists(List lists[]);

#endif