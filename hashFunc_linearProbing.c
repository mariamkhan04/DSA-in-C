#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 6

struct HashNode {
    int keyvalue;
};

struct HashTable {
    struct HashNode* table[TABLE_SIZE];
};

struct HashTable* createHashTable() {
    struct HashTable* newTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        newTable->table[i] = NULL;
    }
    return newTable;
}

int hashFunction(int keyvalue) {
    return keyvalue % TABLE_SIZE;
}

void insert(struct HashTable* ht, int keyvalue) {
    int index = hashFunction(keyvalue);
    while (ht->table[index] != NULL) {
        // Linear probing
        index = (index + 1) % TABLE_SIZE;
    }

    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->keyvalue = keyvalue;
    ht->table[index] = newNode;
}

int search(struct HashTable* ht, int keyvalue, int* foundIndex) {
    int index = hashFunction(keyvalue);

    while (ht->table[index] != NULL) {
        if (ht->table[index]->keyvalue == keyvalue) {
            *foundIndex = index; // Set the foundIndex
            return ht->table[index]->keyvalue;
        }

        // Linear probing
        index = (index + 1) % TABLE_SIZE;
    }

    return -1;  // Keyvalue not found
}

int main() {
    struct HashTable* ht = createHashTable();
    int choice, keyvalue;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert keyvalue\n");
        printf("2. Search for a keyvalue\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter keyvalue: ");
                scanf("%d", &keyvalue);
                insert(ht, keyvalue);
                printf("Keyvalue inserted successfully.\n");
                break;
            case 2:
                printf("Enter keyvalue to search: ");
                scanf("%d", &keyvalue);
                int result, foundIndex;
                result = search(ht, keyvalue, &foundIndex);
                if (result != -1) {
                    printf("Keyvalue found at index %d, value is %d\n", foundIndex, result);
                } else {
                    printf("Keyvalue not found in the hash table.\n");
                }
                break;
            case 3:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
