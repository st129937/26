#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int* input_node(int len) { 
    int* arr = malloc(len * sizeof(int)); 
    if (!arr) return NULL;
    
    for (int i = 0; i < len; i++) { 
        printf("Введите %d элемент: ", i + 1);
        scanf("%d", &arr[i]);
    }
    return arr;
}

Node* create_node(int data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->next = node->prev = node;
    return node;
}

int find_next_id(List lists[]) {
    for (int i = 0; i < 10; i++) {
        if (!lists[i].exists) {
            return i;
        }
    }
    return -1;
}


void create_empty_node(List lists[], int id) {
    lists[id].current = NULL;
    lists[id].exists = 1;
}

void copy_list(List lists[], int from_id, int to_id) {
    if (lists[to_id].current != NULL) {
        printf("Список %d уже существует.\n", to_id);
        return;
    }
    
    Node* src = lists[from_id].current;
    if (!src) return;

    Node* new_head = create_node(src->data);
    Node* prev_new = new_head;
    Node* iter = src->next;

    while (iter != src) {
        Node* new_node = create_node(iter->data);
        new_node->prev = prev_new;
        prev_new->next = new_node;
        prev_new = new_node;
        iter = iter->next;
    }

    new_head->prev = prev_new;
    prev_new->next = new_head;
    lists[to_id].current = new_head;
}

void switch_active_list(List lists[], int* active_list_id, int new_id) {
    if (new_id >= 0 && new_id < 10 && lists[new_id].current != NULL) {
        *active_list_id = new_id;
    } else {
        printf("Список %d не существует.\n", new_id);
    }
}

void insert_after(List lists[], int active_list_id) {
    Node* curr = lists[active_list_id].current;

    int data;
    printf("Значение для вставки после текущего: ");
    scanf("%d", &data);

    Node* new_node = create_node(data);

    if (!curr) {
        new_node->next = new_node;
        new_node->prev = new_node;
        lists[active_list_id].current = new_node;
        return;
    }

    new_node->next = curr->next;
    new_node->prev = curr;
    curr->next->prev = new_node;
    curr->next = new_node;
}


void insert_before(List lists[], int active_list_id) {
    Node* curr = lists[active_list_id].current;

    int data;
    printf("Значение для вставки перед текущим: ");
    scanf("%d", &data);

    Node* new_node = create_node(data);

    if (!curr) {
        new_node->next = new_node;
        new_node->prev = new_node;
        lists[active_list_id].current = new_node;
        return;
    }

    new_node->prev = curr->prev;
    new_node->next = curr;
    curr->prev->next = new_node;
    curr->prev = new_node;
}


void delete_current(List lists[], int active_list_id) {
    Node* curr = lists[active_list_id].current;
    if (!curr) return;

    if (curr->next == curr) {
        free(curr);
        lists[active_list_id].current = NULL;
        return;
    }

    Node* next = curr->next;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    free(curr);
    lists[active_list_id].current = next;
}

void go_forward(List lists[], int active_list_id) {
    if (lists[active_list_id].current)
        lists[active_list_id].current = lists[active_list_id].current->next;
}

void go_back(List lists[], int active_list_id) {
    if (lists[active_list_id].current)
        lists[active_list_id].current = lists[active_list_id].current->prev;
}

void print_all_lists(List lists[], int active_list_id) {
    printf("\n==== Списки ====\n");
    for (int i = 0; i < 10; i++) {
        if (!lists[i].exists) continue;
    
        Node* current = lists[i].current;
    
        if (i == active_list_id) printf(">%d: ", i);
        else printf(" %d: ", i);
    
        if (!current) {
            printf("(пусто)\n");
            continue;
        }
    
        Node* start = current;
        Node* iter = start;
        do {
            if (iter == current) printf("%d* ", iter->data);
            else printf("%d ", iter->data);
            iter = iter->next;
        } while (iter != start);
        printf("\n");
    }
    
    printf("================\n");
}

void free_all_lists(List lists[]) {
    for (int i = 0; i < 10; i++) {
        Node* start = lists[i].current;
        if (!start) continue;

        Node* iter = start->next;
        while (iter != start) {
            Node* tmp = iter;
            iter = iter->next;
            free(tmp);
        }
        free(start);
        lists[i].current = NULL;
        lists[i].exists = 0;
    }
}