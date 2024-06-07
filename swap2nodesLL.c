#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int id;
    int marks;
    struct Node* next;
};

struct Node* start = NULL;

// Function to insert a new node at the end of the list
void insert() {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    printf("Enter id: ");
    scanf("%d", &temp->id);
    printf("Enter Marks: ");
    scanf("%d", &temp->marks);
    temp->next = NULL;
    if (start == NULL) {
        start = temp;
    } else {
        struct Node* curr = start;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = temp;
    }
}

// Function to print the linked list
void printLinkedList() {
    struct Node* curr = start;
    printf("Linked List is: \n");
    while (curr != NULL) {
        printf("ID is: %d\n", curr->id);
        printf("Marks are: %d\n", curr->marks);
        curr = curr->next;
    }
}

// Function to search for a specific ID in the list
void search() {
    int toSearchId;
    printf("Enter the ID you want to find: ");
    scanf("%d", &toSearchId);
    struct Node* curr = start;
    while (curr != NULL) {
        if (toSearchId == curr->id) {
            printf("Id found: %d\nMarks at Id: %d\n", curr->id, curr->marks);
            break;
        }
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Element not found\n");
    }
}

// Function to delete a single node by ID
void delete() {
    struct Node* curr = start;
    int toDeleteId;
    printf("Enter id : ");
    scanf("%d", &toDeleteId);
    if (toDeleteId == start->id) {
        start = start->next;
        free(curr);
    } else {
        struct Node* prev = start;
        curr = start->next;
        while (curr != NULL) {
            if (curr->id == toDeleteId) {
                prev->next = curr->next;
                free(curr);
                break;
            } else {
                prev = prev->next;
                curr = curr->next;
            }
        }
        if (curr == NULL) {
            printf("Element not found\n");
        }
    }
}

// Function to delete the entire list
void deleteAll() {
    struct Node* curr = start;
    while (curr != NULL) {
        struct Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    start = NULL;
    printf("All Nodes deleted\n");
}

// Function to swap two nodes in the list
void swapNodes(int id1, int id2) {
    struct Node* prev1 = NULL;
    struct Node* curr1 = start;
    while (curr1 != NULL && curr1->id != id1) {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    struct Node* prev2 = NULL;
    struct Node* curr2 = start;
    while (curr2 != NULL && curr2->id != id2) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if (curr1 == NULL || curr2 == NULL) {
        printf("One or both of the IDs not found.\n");
        return;
    }

    if (prev1 != NULL) {
        prev1->next = curr2;
    } else {
        start = curr2;
    }

    if (prev2 != NULL) {
        prev2->next = curr1;
    } else {
        start = curr1;
    }

    struct Node* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;

    printf("Nodes with IDs %d and %d swapped.\n", id1, id2);
}

int main() {
    int choice, listSize;
    bool flag = true;
    while (flag == true) {
        printf("\tOptions\t\n");
        printf("1. Insert\n");
        printf("2. Print\n");
        printf("3. Search\n");
        printf("4. DeleteNode\n");
        printf("5. DeleteAll\n");
        printf("6. SwapNodes\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter list size: ");
                scanf("%d", &listSize);
                for (int i = 0; i < listSize; i++) {
                    insert();
                }
                break;
            case 2:
                printLinkedList();
                break;
            case 3:
                search();
                break;
            case 4:
                delete();
                break;
            case 5:
                deleteAll();
                break;
            case 6:
                {
                    int id1, id2;
                    printf("Enter the IDs of the nodes you want to swap: ");
                    scanf("%d %d", &id1, &id2);
                    swapNodes(id1, id2);
                }
                break;
            case 7:
                printf("Program Finished\n");
                flag = false;
                break;
            default:
                printf("Enter a valid choice!\n");
        }
    }
    return 0;
}
