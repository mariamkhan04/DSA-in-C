#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define size 10

struct HtNode {
    int value;
    struct HtNode* next;
};

int hashFunc(int keyValue) {
    return keyValue % size;
}

void initializeHashTable(struct HtNode* HTable) {
    for (int i = 0; i < size; i++) {
        HTable[i].value = -1;
        HTable[i].next = NULL; // Initialize the next field to NULL
    }
}

void insert(struct HtNode* HTable, int keyValue) {
    int ind = hashFunc(keyValue);

    if (HTable[ind].value == -1) {
        // No collision, insert at the beginning of the list
        HTable[ind].value = keyValue;
    } else {
        // Collision, insert at the end of the list
        struct HtNode* temp = (struct HtNode*)malloc(sizeof(struct HtNode));
        temp->value = keyValue;
        temp->next = NULL;
        if (HTable[ind].next == NULL) {
            HTable[ind].next = temp;
        } else {
            struct HtNode* curr = HTable[ind].next;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = temp;
        }
    }
}

int search(struct HtNode* HTable, int keyValue) {
    int ind = hashFunc(keyValue);
    
    if (HTable[ind].value == keyValue) {
        return ind; // Found in the main slot
    } else {
        struct HtNode* curr = HTable[ind].next;
        while (curr != NULL) {
            if (curr->value == keyValue) {
                return ind; // Found in the linked list
            }
            curr = curr->next;
        }
    }
    
    return -1; // Not found
}

void deleteKey(struct HtNode* HTable, int keyValue) {
    int ind = hashFunc(keyValue);
    
    if (HTable[ind].value == keyValue) {
        // Delete from the main slot
        HTable[ind].value = -1;
    } else {
        struct HtNode* prev = &HTable[ind];
        struct HtNode* curr = HTable[ind].next;
        while (curr != NULL) {
            if (curr->value == keyValue) {
                // Delete from the linked list
                prev->next = curr->next;
                free(curr);
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }
}

void print(struct HtNode* HTable) {
    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        struct HtNode* current = &HTable[i]; // Start from HTable[i]
        while (current != NULL) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("\n");
}

int main() {
    struct HtNode HTable[size];
    initializeHashTable(HTable);

    int choice, keyValue, result;
    bool flag = true;

    while (flag) {
        printf("MENU\n1. Insert\n2. Print\n3. Search\n4. Delete\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key value: ");
                scanf("%d", &keyValue);
                insert(HTable, keyValue);
                break;
            case 2:
                print(HTable);
                break;
            case 3:
                printf("Enter key value to search: ");
                scanf("%d", &keyValue);
                result = search(HTable, keyValue);
                if (result != -1) {
                    printf("Key %d found at index %d\n", keyValue, result);
                } else {
                    printf("Key %d not found\n", keyValue);
                }
                break;
            case 4:
                printf("Enter key value to delete: ");
                scanf("%d", &keyValue);
                deleteKey(HTable, keyValue);
                break;
            case 5:
                flag = false;
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    // Free allocated memory for the linked list nodes
    for (int i = 0; i < size; i++) {
        struct HtNode* current = HTable[i].next;
        while (current != NULL) {
            struct HtNode* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
