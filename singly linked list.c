#include <stdio.h>
#include <stdlib.h>

typedef struct data {
    int number_of_node;
    struct data* next;
} node;

node* node_init(int*);
void insert_to_list(node**, node*);
void print_list(node*);
node* node_search(node*, int);
void insert_after(node*, node*);
void delete_list(node**);
void delete_node(node**, node*);
int main(void) {
    node* start = NULL;
    int node_number = 0;
    node* found_node;
    int choice_2;
    int choice_3;
    while (1) {
        printf("What do you want to do?\n");
        printf("1 - add a node to the list\n2 - delete a node from the list\n3 - delete the list\n");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Where do you want the node to be placed?\n");
                printf("1 - at the start of the list\n2 - some other place\n");
                scanf("%d", &choice_2);
                if (choice_2 == 1) insert_to_list(&start, node_init(&node_number));
                if (choice_2 == 2) {
                    printf("Where do you want to insert the node?\n");
                    scanf("%d", &choice_3);
                    found_node = node_search(start, choice_3);
                    insert_after(found_node, node_init(&node_number));
                }
                if (choice_2 != 1 && choice_2 != 2) printf("No such option, try again\n");
                break;
            case 2:
                printf("Choose the node to delete\n");
                int ntd;
                scanf("%d", &ntd);
                found_node = node_search(start, ntd);
                if (found_node) {
                    delete_node(&start, found_node);
                } else {
                    printf("No nodes found at this position");
                }
                break;
            case 3:
                if (start != NULL) {
                    delete_list(&start);
                    printf("The list is no more");
                } else {
                    printf("There is no list yet, nothing to delete");
                }
                break;
        }
        if (start != NULL) print_list(start);
        printf("\n");
    }

    return 0;
}

node* node_init(int* node_number) {
    node* new_node = malloc(sizeof(node));
    new_node->number_of_node = *node_number;
    new_node->next = NULL;
    (*node_number)++;
    return new_node;
}

void insert_to_list(node** start, node* new_node) {
    new_node->next = *start;
    *start = new_node;
}

void print_list(node* start) {
    node* ptr = start;
    while (ptr) {
        printf("%d ", ptr->number_of_node);
        ptr = ptr->next;
    }
}

node* node_search(node* start, int node_id) {
    node* ptr = start;
    while (ptr && ptr->number_of_node != node_id) {
        ptr = ptr->next;
    }
    return ptr;
}

void insert_after(node* node_to_insert_after, node* node_to_insert) {
    if (node_to_insert_after == NULL) {
        printf("There is no node to insert after at this position\n");
        free(node_to_insert);
        return;
    }

    node_to_insert->next = node_to_insert_after->next;
    node_to_insert_after->next = node_to_insert;
}

void delete_list(node** start) {
    node* ptr = *start;
    while (ptr) {
        node* next = ptr->next;
        free(ptr);
        ptr = next;
    }
    *start = NULL;
}

void delete_node(node** start, node* node_to_remove) {
    if (*start == NULL || node_to_remove == NULL) return;
    node* ptr = *start;
    if (*start == node_to_remove) {
        *start = node_to_remove->next;
        free(node_to_remove);
    } else {
        while (ptr && ptr->next != node_to_remove) {
            ptr = ptr->next;
        }
        if (ptr) {
            ptr->next = node_to_remove->next;
            free(node_to_remove);
        }
    }
}
