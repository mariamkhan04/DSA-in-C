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

struct Node* convertMaxHeapToCompleteTree(int arr[], int size, int i) {
    if (i < size) {
        struct Node* root = createNode(arr[i]);
        root->left = convertMaxHeapToCompleteTree(arr, size, 2 * i + 1);
        root->right = convertMaxHeapToCompleteTree(arr, size, 2 * i + 2);
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

    struct Node* completeBinaryTree = convertMaxHeapToCompleteTree(arr, size, 0);

    printf("Inorder Traversal of the Complete Binary Tree: ");
    inorderTraversal(completeBinaryTree);
    printf("\n");

    // Free the dynamically allocated array
    free(arr);

    return 0;
}
