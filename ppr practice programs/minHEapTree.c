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

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to build a min heap
void buildMinHeap(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int child = i;
        while (child > 0) {
            int parent = (child - 1) / 2;
            if (arr[child] < arr[parent]) {
                swap(&arr[child], &arr[parent]);
                child = parent;
            } else {
                break;
            }
        }
    }
}

struct Node* buildMinHeapTree(int arr[], int size, int i) {
    if (i < size) {
        struct Node* root = createNode(arr[i]);
        root->left = buildMinHeapTree(arr, size, 2 * i + 1);
        root->right = buildMinHeapTree(arr, size, 2 * i + 2);
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

    // Build a min heap
    buildMinHeap(arr, size);

    printf("Min Heap Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    struct Node* minHeapRoot = buildMinHeapTree(arr, size, 0);

    printf("Inorder Traversal of the Min Heap Tree: ");
    inorderTraversal(minHeapRoot);
    printf("\n");

    free(arr); // Free the dynamically allocated array
    return 0;
}