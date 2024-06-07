/*A program in c that takes to binary trees T1 and T2 as input and perform the following tasks:
1. checks whether the two binary trees T1 and T2 are equal , equal tree are those that has same data on same node.
2. checks whether the two binary trees T1 and T2 have same structure, trees having same structure have same number of children for each node but the values stored at nodes can be different.
3. checks whether two binary trees T1 and T2 are mirror image of eachother , a tree is the mirror image of the other tree if for each node the value on the left child of the root is same as the right child value of the other tree and viceversa 
where T1 and T2 are any two binary trees in which the nodes hold the string data
use this method of bst as standard:
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Node {
    char data[50];  // Use an array of characters to store string data
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(const char* value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    strncpy(temp->data, value, sizeof(temp->data));  // Use strncpy to copy the string
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* root, const char* value) {
    if (root == NULL) {
        return createNode(value);
    }

    // Prompt user for left or right child
    printf("Enter 'L' for left or 'R' for right child of %s: ", root->data);
    char choice;
    scanf(" %c", &choice);

    if (choice == 'L' || choice == 'l') {
        root->left = insert(root->left, value);
    } else if (choice == 'R' || choice == 'r') {
        root->right = insert(root->right, value);
    } else {
        printf("Invalid choice. Please enter 'L' or 'R'.\n");
    }

    return root;
}

// Function to check if two binary trees are equal
bool areEqual(struct Node* t1, struct Node* t2) {
    if (t1 == NULL && t2 == NULL) {
        return true;  // Both trees are empty, so they are equal.
    }
    if (t1 != NULL && t2 != NULL) {
        return (strcmp(t1->data, t2->data) == 0) &&
               areEqual(t1->left, t2->left) &&
               areEqual(t1->right, t2->right);
    }
    return false;  // If one tree is empty and the other is not, they are not equal.
}

// Function to check if two binary trees have the same structure
bool haveSameStructure(struct Node* t1, struct Node* t2) {
    if (t1 == NULL && t2 == NULL) {
        return true;  // Both trees are empty, so they have the same structure.
    }
    if (t1 != NULL && t2 != NULL) {
        return haveSameStructure(t1->left, t2->left) &&
               haveSameStructure(t1->right, t2->right);
    }
    return false;  // If one tree is empty and the other is not, they do not have the same structure.
}

// Function to check if two binary trees are mirror images
bool areMirrorImages(struct Node* t1, struct Node* t2) {
    if (t1 == NULL && t2 == NULL) {
        return true;  // Both trees are empty, so they are mirror images.
    }
    if (t1 != NULL && t2 != NULL) {
        return (strcmp(t1->data, t2->data) == 0) &&
               areMirrorImages(t1->left, t2->right) &&
               areMirrorImages(t1->right, t2->left);
    }
    return false;  // If one tree is empty and the other is not, they are not mirror images.
}

int main() {
    struct Node* root1 = NULL;
    struct Node* root2 = NULL;
    char value[50];  // Use a character array for string input
    char choice;

    // Build the first binary tree (T1)
    do {
        printf("Enter value for T1: ");
        scanf("%s", value);
        root1 = insert(root1, value);
        printf("Do you want to insert another value in T1? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    // Build the second binary tree (T2)
    do {
        printf("Enter value for T2: ");
        scanf("%s", value);
        root2 = insert(root2, value);
        printf("Do you want to insert another value in T2? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    // Check if T1 and T2 are equal
    if (areEqual(root1, root2)) {
        printf("T1 and T2 are equal.\n");
    } else {
        printf("T1 and T2 are not equal.\n");
    }

    // Check if T1 and T2 have the same structure
    if (haveSameStructure(root1, root2)) {
        printf("T1 and T2 have the same structure.\n");
    } else {
        printf("T1 and T2 do not have the same structure.\n");
    }

    // Check if T1 and T2 are mirror images
    if (areMirrorImages(root1, root2)) {
        printf("T1 and T2 are mirror images.\n");
    } else {
        printf("T1 and T2 are not mirror images.\n");
    }

    return 0;
}
