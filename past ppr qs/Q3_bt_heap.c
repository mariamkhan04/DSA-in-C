/*build a binary tree by inserting elements in same manner as nodes are inserted in heap i.e from left to right . Each node should hold a string value.
given a pointer to the root of binary tree:
1. find its mirror image: mirror image of the tree is build such that the left child is now the right child and right is now the left child. 
2. given an element x find the predecessors and successors of x, if x exists
3. Find the level of any element x in the tree , if x exists
4. find the height of node of any element x in the tree , if x exists*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data[100];  // Assuming a maximum string length of 100 characters
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(const char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* buildCompleteBTree(const char* arr[], int size, int i) {
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
        printf("%s ", root->data);
        inorderTraversal(root->right);
    }
}

void mirrorImage(struct Node* root) {
    if (root == NULL) {
        return;
    }

    // Recursively swap the left and right subtrees
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Apply mirrorImage to the left and right subtrees
    mirrorImage(root->left);
    mirrorImage(root->right);
}

struct Node* findNode(struct Node* root, const char* x) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(root->data, x) == 0) {
        return root;
    }

    struct Node* left = findNode(root->left, x);
    struct Node* right = findNode(root->right, x);

    return left ? left : right;
}

struct Node* findSuccessor(struct Node* root, const char* x) {
    struct Node* node = findNode(root, x);

    if (node == NULL || node->right == NULL) {
        return NULL;
    }

    node = node->right;
    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

struct Node* findPredecessor(struct Node* root, const char* x) {
    struct Node* node = findNode(root, x);

    if (node == NULL || node->left == NULL) {
        return NULL;
    }

    node = node->left;
    while (node->right != NULL) {
        node = node->right;
    }

    return node;
}

int findLevel(struct Node* root, const char* x, int level) {
    if (root == NULL) {
        return -1; // Element not found
    }

    if (strcmp(root->data, x) == 0) {
        return level;
    }

    int leftLevel = findLevel(root->left, x, level + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }

    int rightLevel = findLevel(root->right, x, level + 1);
    return rightLevel;
}
int getHeight(struct Node* root, const char* x){
    if (root==NULL){
      return -1;
    }
    int leftHeight=getHeight(root->left,x);
    int rightHeight=getHeight(root->right,x);
    return (leftHeight>rightHeight? leftHeight : rightHeight)+1;
}

int main() {
    int size;
    printf("Enter the number of elements in the string array: ");
    scanf("%d", &size);
    
    if (size <= 0) {
        printf("Invalid array size. Exiting...\n");
        return 1;
    }
    
    const char** arr = (const char**)malloc(size * sizeof(const char*)); //pointer to an array of strings.
    
    for (int i = 0; i < size; i++) {
        printf("Enter element %d: ", i + 1);
        char element[100];
        scanf("%s", element);
        arr[i] = (const char*)malloc(strlen(element) + 1);
        strcpy((char*)arr[i], element);
    }
    
    struct Node* root = buildCompleteBTree(arr, size, 0);
    
    int choice;
    char x[100];  // Assuming a maximum string length of 100 characters
    struct Node* node;

    do {
        printf("\nMenu:\n");
        printf("1. Display Inorder Traversal\n");
        printf("2. Find Mirror Image\n");
        printf("3. Find Successor of Element\n");
        printf("4. Find Predecessor of Element\n");
        printf("5. Find Level of Element\n");
        printf("6. Find Height of Node\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Inorder Traversal of the Complete Binary Tree: ");
                inorderTraversal(root);
                printf("\n");
                break;

            case 2:
                mirrorImage(root);
                printf("Mirror image created.\n");
                printf("Inorder Traversal of the Mirror Image: ");
                inorderTraversal(root);
                printf("\n");
                break;

            case 3:
                printf("Enter element to find its successor: ");
                scanf("%s", x);
                node = findNode(root, x);
                if (node) {
                    struct Node* successor = findSuccessor(root, x);
                    if (successor) {
                        printf("Successor of %s is %s\n", x, successor->data);
                    } else {
                        printf("Element not found or has no successor.\n");
                    }
                } else {
                    printf("Element not found.\n");
                }
                break;

            case 4:
                printf("Enter element to find its predecessor: ");
                scanf("%s", x);
                node = findNode(root, x);
                if (node) {
                    struct Node* predecessor = findPredecessor(root, x);
                    if (predecessor) {
                        printf("Predecessor of %s is %s\n", x, predecessor->data);
                    } else {
                        printf("Element not found or has no predecessor.\n");
                    }
                } else {
                    printf("Element not found.\n");
                }
                break;

            case 5:
                printf("Enter element to find its level: ");
                scanf("%s", x);
                node = findNode(root, x);
                if (node) {
                    int level = findLevel(root, x, 0);
                    printf("Level of %s is %d\n", x, level);
                } else {
                    printf("Element not found.\n");
                }
                break;

            case 6:
                printf("Enter element to find its height: ");
                scanf("%s", x);
                node = findNode(root, x);
                if (node) {
                    int height = getHeight(node, x);
                    printf("Height of node containing %s is %d\n", x, height);
                } else {
                    printf("Element not found.\n");
                }
                break;

            case 0:
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Free allocated memory for the array
    for (int i = 0; i < size; i++) {
        free((char*)arr[i]);
    }
    free(arr);

    return 0;
}
