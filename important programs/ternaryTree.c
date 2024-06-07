#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TernaryNode {
    int data;
    struct TernaryNode* left;
    struct TernaryNode* middle;
    struct TernaryNode* right;
};

struct TernaryNode* createTernaryNode(int value) {
    struct TernaryNode* temp = (struct TernaryNode*)malloc(sizeof(struct TernaryNode));
    temp->data = value;
    temp->left = NULL;
    temp->middle = NULL;
    temp->right = NULL;
    return temp;
}

struct TernaryNode* insert(struct TernaryNode* root, int value) {
    if (root == NULL) {
        return createTernaryNode(value);
    }

    // Prompt user for left, middle, or right child
    printf("Enter 'L' for left, 'M' for middle, or 'R' for right child of %d: ", root->data);
    char choice;
    scanf(" %c", &choice);

    if (choice == 'L' || choice == 'l') {
        root->left = insert(root->left, value);
    } else if (choice == 'M' || choice == 'm') {
        root->middle = insert(root->middle, value);
    } else if (choice == 'R' || choice == 'r') {
        root->right = insert(root->right, value);
    } else {
        printf("Invalid choice. Please enter 'L', 'M', or 'R'.\n");
    }

    return root;
}

bool search(struct TernaryNode* root, int value) {
    if (root == NULL) {
        return false;
    }

    if (root->data == value) {
        return true;
    }

    // Recursively search in the left, middle, and right subtrees
    bool foundInLeft = search(root->left, value);
    bool foundInMiddle = search(root->middle, value);
    bool foundInRight = search(root->right, value);

    return foundInLeft || foundInMiddle || foundInRight;
}
// struct TernaryNode* delete(struct TernaryNode* node, int value) {
//     if (node == NULL) {
//         return NULL; // If the node is null, return null address
//     }

//     if (value == node->data) {
//         // Node has no children
//         if (node->left == NULL && node->middle == NULL && node->right == NULL) {
//             free(node);
//             return NULL;
//         }

//         // Node has one child
//         if (node->left == NULL) {
//             struct TernaryNode* temp = node->middle ? node->middle : node->right;
//             free(node);
//             return temp;
//         } else if (node->middle == NULL) {
//             struct TernaryNode* temp = node->left ? node->left : node->right;
//             free(node);
//             return temp;
//         } else if (node->right == NULL) {
//             struct TernaryNode* temp = node->left ? node->left : node->middle;
//             free(node);
//             return temp;
//         }

//         // Node has three children
//         struct TernaryNode* smallest = node->right;
//         while (smallest->left != NULL) {
//             smallest = smallest->left;
//         }

//         node->data = smallest->data;
//         node->right = delete(node->right, smallest->data);
//     } else {
//         node->left = delete(node->left, value);
//         node->middle = delete(node->middle, value);
//         node->right = delete(node->right, value);
//     }
//     return node;
// }
void inorder(struct TernaryNode* node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d\t", node->data);
        inorder(node->middle);
        inorder(node->right);
    }
}

int main() {
    struct TernaryNode* root = NULL;
    int value, choice;
    bool flag = true;

    while (flag) {
        printf("MENU: \n1. Insert\n2. Search\n3. Delete\n4. Print\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
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
            // case 3:
            //     printf("Enter value to delete: ");
            //     scanf("%d", &value);
            //     root = delete(root, value);
            //     break;
            case 4:
                inorder(root);
                break;
            case 5:
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
