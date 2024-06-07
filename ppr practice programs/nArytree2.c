#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHILDREN 5

struct NaryNode {
    int data;
    struct NaryNode* children[MAX_CHILDREN]; //array of pointers to NaryNode structures, which represents the child nodes of the current node. The array can hold a maximum of MAX_CHILDREN child nodes.
    int numChildren; //keeps track of how many child nodes the current node has. It's initialized to 0 because a new node starts with no children.
};

struct NaryNode* createNaryNode(int value) {
    struct NaryNode* temp = (struct NaryNode*)malloc(sizeof(struct NaryNode));
    temp->data = value;
    temp->numChildren = 0; //a new node starts with no children.
    //This loop initializes each element of the children array to NULL, indicating that the new node has no child nodes yet.
    for (int i = 0; i < MAX_CHILDREN; i++) {
        temp->children[i] = NULL;
    }
    return temp;
}
void insert(struct NaryNode* parent, int value) {
    if (parent == NULL) {
        printf("Cannot insert into a null parent node.\n");
        return;
    }

    if (parent->numChildren < MAX_CHILDREN) {
        parent->children[parent->numChildren] = createNaryNode(value);
        parent->numChildren++;
    } else {
        // Find the leftmost child that has room for the new node
        for (int i = 0; i < parent->numChildren; i++) {
            if (parent->children[i]->numChildren < MAX_CHILDREN) {
                insert(parent->children[i], value);
                return; // Inserted the value, so exit the function
            }
        }
        
        // If no child has room, print an error message
        printf("Max number of children reached for this node and its descendants.\n");
    }
}

bool search(struct NaryNode* root, int value) {
    if (root == NULL) {
        return false;
    }

    if (root->data == value) {
        return true;
    }

    for (int i = 0; i < root->numChildren; i++) {
        if (search(root->children[i], value)) {
            return true;
        }
    }

    return false;
}

void inorder(struct NaryNode* node) {
    if (node != NULL) {
        printf("%d\t", node->data);
        for (int i = 0; i < node->numChildren; i++) {
            inorder(node->children[i]);
        }
    }
}

int main() {
    struct NaryNode* root = createNaryNode(2);
    int value, choice;
    bool flag = true;

    while (flag) {
        printf("MENU: \n1. Insert\n2. Search\n3. Print\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(root, value);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value)) {
                    printf("Value found\n");
                } else {
                    printf("Value not found\n");
                }
                break;
            case 3:
                printf("N-ary Tree: ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Program finished!\n");
                flag = false;
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}
