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
struct Node* buildCompleteBTree(int arr[], int size, int i) {
    if (i < size) {
        struct Node* root = createNode(arr[i]);
        root->left = buildCompleteBTree(arr, size, 2 * i + 1);
        root->right = buildCompleteBTree(arr, size, 2 * i + 2);
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
    int* arr = NULL;
    int size = 0;
    int value;

    printf("Enter values one by one (Enter -1 to stop):\n");

    while (1) {
        scanf("%d", &value);
        if (value == -1) {
            break;
        }
        size++;
        arr = (int*)realloc(arr, size * sizeof(int));
        arr[size - 1] = value;
    }
    struct Node *root =buildCompleteBTree(arr, size, 0);
    printf("Inorder Traversal of the Complete Binary Tree: ");
    inorderTraversal(root);
    printf("\n");

    free(arr); // Free the dynamically allocated array
    return 0;
}