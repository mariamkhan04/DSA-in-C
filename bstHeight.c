// program to calculate the height of each node in bst
#include <stdio.h>
#include <stdlib.h>

struct BSTNode {
  int data;
  struct BSTNode *left;
  struct BSTNode *right;
};

// Function to insert a value in BST
struct BSTNode *insert(struct BSTNode *node, int value){
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
  return node;
}
int getHeight(struct BSTNode *node) {
    if (node == NULL) {
        return -1;
    }
    int left_height = getHeight(node->left);
    int right_height = getHeight(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}
void inOrder(struct BSTNode *node){
    if(node!=NULL ){
        inOrder(node->left);
        printf("%d height:%d\n",node->data,getHeight(node));
        inOrder(node->right);
    }
}

int main() {
  struct BSTNode *Root = NULL;
  int choice,value;
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
        inOrder(Root);
        break;
      case 3:
        exit(0);
        break;

      default:
        printf("Invalid choice!\n");
        break;
    }
  } while (choice != 3);

  return 0;
}
