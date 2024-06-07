#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct BSTNode {
  int data;
  struct BSTNode *left;
  struct BSTNode *right;
};

int getHeight(struct BSTNode *node) {
    if (node == NULL) {
        return -1;
    }
    int left_height = getHeight(node->left);
    int right_height = getHeight(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

int getBalanceFactor(struct BSTNode *node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

struct BSTNode *shiftLeft(struct BSTNode *node) {
    struct BSTNode *newRoot = node->right;
    struct BSTNode *T2 = newRoot->left;

    newRoot->left = node;
    node->right = T2;

    return newRoot;
}

struct BSTNode *shiftRight(struct BSTNode *node) {
    struct BSTNode *newRoot = node->left;
    struct BSTNode *T2 = newRoot->right;

    newRoot->right = node;
    node->left = T2;

    return newRoot;
}

struct BSTNode *insert(struct BSTNode *node, int value) {
    if (node == NULL) {
        struct BSTNode *temp = (struct BSTNode *)malloc(sizeof(struct BSTNode));
        temp->data = value;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }

    if (value > node->data) {
        node->right = insert(node->right, value);
    } else {
        node->left = insert(node->left, value);
    }

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (value < node->left->data) {
            // Left-Left condition
            node = shiftRight(node);
        } else {
            // Left-Right condition
            node->left = shiftLeft(node->left);
            node = shiftRight(node);
        }
    } else if (balanceFactor < -1) {
        if (value > node->right->data) {
            // Right-Right condition
            node = shiftLeft(node);
        } else {
            // Right-Left condition
            node->right = shiftRight(node->right);
            node = shiftLeft(node);
        }
    }

    return node;
}

void PreOrder(struct BSTNode *node) {
    if (node != NULL) {
        printf("%d balance:%d\n", node->data, getBalanceFactor(node));
        PreOrder(node->left);
        PreOrder(node->right);
    }
}

int main() {
    struct BSTNode *Root = NULL;
    int choice;
    int value;
    bool flag = true;

    do {
        printf("Menu:\n");
        printf("1. Insert\n");
        printf("2. Print\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                Root = insert(Root, value);
                break;

            case 2:
                PreOrder(Root);
                break;

            case 3:
                printf("Program finished\n");
                flag = false;
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (flag == true);

    return 0;
}
