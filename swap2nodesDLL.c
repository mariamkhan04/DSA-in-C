#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int id;
    int marks;
    struct Node* next;
    struct Node* prev;
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
    temp->prev = NULL;

    if (start == NULL) {
        start = temp;
    } else {
        struct Node* curr = start;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = temp;
        temp->prev = curr;
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
    int toDeleteId;
    printf("Enter id : ");
    scanf("%d", &toDeleteId);

    struct Node* curr = start;
    while (curr != NULL) {
        if (curr->id == toDeleteId) {
            if (curr->prev != NULL) {
                curr->prev->next = curr->next;
            } else {
                start = curr->next;
            }

            if (curr->next != NULL) {
                curr->next->prev = curr->prev;
            }

            free(curr);
            printf("Node with ID %d deleted.\n", toDeleteId);
            return;
        }
        curr = curr->next;
    }

    printf("Element not found\n");
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
    struct Node* node1 = NULL;
    struct Node* node2 = NULL;
    struct Node* curr = start;

    // Find nodes with id1 and id2
    while (curr != NULL) {
        if (curr->id == id1) {
            node1 = curr;
        } else if (curr->id == id2) {
            node2 = curr;
        }

        curr = curr->next;
    }

    if (node1 == NULL || node2 == NULL) {
        printf("One or both of the IDs not found.\n");
        return;
    }

    // Swap prev pointers
    struct Node* tempPrev = node1->prev;
    node1->prev = node2->prev;
    node2->prev = tempPrev;

    // Swap next pointers
    struct Node* tempNext = node1->next;
    node1->next = node2->next;
    node2->next = tempNext;

    // Update adjacent nodes' next and prev pointers
    if (node1->prev != NULL) {
        node1->prev->next = node2;
    } else {
        start = node2;
    }

    if (node1->next != NULL) {
        node1->next->prev = node2;
    }

    if (node2->prev != NULL) {
        node2->prev->next = node1;
    } else {
        start = node1;
    }

    if (node2->next != NULL) {
        node2->next->prev = node1;
    }

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
