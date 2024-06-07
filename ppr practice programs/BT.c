#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    // Prompt user for left or right child
    printf("Enter 'L' for left or 'R' for right child of %d: ", root->data);
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
bool search(struct Node* root, int value) {
    if (root == NULL) {
        return false;
    }

    if (root->data == value) {
        return true;
    }

    // Recursively search in the left and right subtrees
    bool foundInLeft = search(root->left, value);
    bool foundInRight = search(root->right, value);

    return foundInLeft || foundInRight;
}
// Function to delete a node
struct Node* delete(struct Node *node, int value) {
     if (node == NULL) {
        return NULL; //if node is null return null address
    }
    if (value==node->data){
    // Node has no children
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }

    // Node has one child
        if (node->left == NULL) {
            struct Node *temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            struct Node *temp = node->left;
            free(node);
            return temp;
        }

    // Node has both children
        struct Node *smallest = node->right;
        while (smallest->left != NULL) {
            smallest = smallest->left;
        }

        node->data = smallest->data;
        node->right = delete(node->right, smallest->data);
    }else{
        node->left = delete(node->left, value);
        node->right = delete(node->right, value);
    }
return node;
}
void inorder(struct Node* node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d\t", node->data);
        inorder(node->right);
    }
}

int main() {
    struct Node* root = NULL;
    int value,choice;
    bool flag = true;

     while(flag){
        printf("MENU: \n1. Insert\n2. Search\n3. Delete\n4. Print\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d",&value);
            root=insert(root,value);
            break;
        case 2:
            printf("Enter value to search: ");
            scanf("%d",&value);
            if(search(root,value)){
                printf("value found\n");
            }else{
                printf("value not found\n");
            }
            break;
        case 3:
            printf("Enter value to delete: ");
            scanf("%d",&value);
            root=delete(root,value);
            break;
        case 4:
            inorder(root);
            // PreOrderPrint(Root);
            // PostOrderPrint(Root);
            break;
        case 5:
            printf("program finished!");
            flag=false;
            break;
        default:
            printf("Inavlid choice");
            break;
        }
    }
    return 0;
}