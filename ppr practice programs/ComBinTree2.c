#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void userInput(struct Node* root, int level, int maxSize) {
    if (level >= maxSize) {
        return;
    }

    printf("Enter data for level %d: ", level + 1);
    scanf("%d", &root->data);

    if (2 * level + 1 < maxSize) {
        root->left = createNode(0);
        userInput(root->left, 2 * level + 1, maxSize);
    }

    if (2 * level + 2 < maxSize) {
        root->right = createNode(0);
        userInput(root->right, 2 * level + 2, maxSize);
    }
}

void inorderTraversal(struct Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    int size;
    printf("Enter the number of levels: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid number of levels.\n");
        return 1;
    }

    struct Node* root = createNode(0);

    userInput(root, 0, size);

    printf("Inorder Traversal of the Complete Binary Tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
