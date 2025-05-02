#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "list.h"

int main() {
    List lists[10] = {0};
    int active_list_id = 0;
    int x;

    setlocale(LC_CTYPE, "Russian");

    while (1) {
        printf("\n�������� ��������:\n");
        printf("1. ������� ����� ������\n");
        printf("2. ���������� ������\n");
        printf("3. ������� �������� ������\n");
        printf("4. �������� ����� �������� ��������\n");
        printf("5. �������� ����� ������� ���������\n");
        printf("6. ������� ������� �������\n");
        printf("7. ������� � ���������� ��������\n");
        printf("8. ������� � ����������� ��������\n");
        printf("9. ������� ��� ������\n");
        printf("0. �����\n");
        printf("��� �����: ");
        scanf("%d", &x);

        switch (x) {
            case 0:
                free_all_lists(lists);
                return 0;
            case 1: {
                int new_id = find_next_id(lists);
                if (new_id == -1) {
                    printf("������� ����� ������� (10).\n");
                    break;
                }
                
                int length;
                printf("������� ����� ������� (0 ��� ������� ������): ");
                scanf("%d", &length);
                
                if (length == 0) {
                    create_empty_node(lists, new_id);
                    active_list_id = new_id;
                    printf("������ ������ ������ (ID: %d)\n", new_id);
                    break;
                }
                
                int* data = input_node(length);
                if (!data) break;
                
                Node* new_node = create_node(data[0]);
                for (int i = 1; i < length; i++) {
                    Node* n = create_node(data[i]);
                    n->prev = new_node->prev;
                    n->next = new_node;
                    new_node->prev->next = n;
                    new_node->prev = n;
                }
                
                lists[new_id].current = new_node;
                lists[new_id].exists = 1;
                active_list_id = new_id;
                free(data);
                break;
            }
            case 2: {
                int from_id;
                printf("���������� �� ID: ");
                scanf("%d", &from_id);
                if (from_id < 0 || from_id >= 10 || lists[from_id].current == NULL) {
                    printf("�������� ������ %d �� ����������.\n", from_id);
                    break;
                }
                int to_id = find_next_id(lists);
                if (to_id == -1) {
                    printf("������� ����� ������� (10).\n");
                    break;
                }
                copy_list(lists, from_id, to_id);
                break;
            }
            case 3: {
                int new_id;
                printf("����� �������� ������: ");
                scanf("%d", &new_id);
                switch_active_list(lists, &active_list_id, new_id);
                break;
            }
            case 4: insert_after(lists, active_list_id); break;
            case 5: insert_before(lists, active_list_id); break;
            case 6: delete_current(lists, active_list_id); break;
            case 7: go_forward(lists, active_list_id); break;
            case 8: go_back(lists, active_list_id); break;
            case 9: print_all_lists(lists, active_list_id); break;
            default: printf("���������� ��� ���.\n");
        }
    }
    return 0;
}