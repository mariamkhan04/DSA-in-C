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

struct Node* buildCompleteBinaryTree(int arr[], int size, int i) {
    if (i < size) {
        struct Node* root = createNode(arr[i]);
        root->left = buildCompleteBinaryTree(arr, size, 2 * i + 1);
        root->right = buildCompleteBinaryTree(arr, size, 2 * i + 2);
        return root;
    }
    return NULL;
}

void inorderTraversal(struct Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = buildCompleteBinaryTree(arr, size, 0);

    printf("Inorder Traversal of the Complete Binary Tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
