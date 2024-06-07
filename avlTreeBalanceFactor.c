/*(AVL TREE) Program to insert nodes in a bst and balancing the tree when it becomes unbalanced by shifting left Operation */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct BSTNode {
  int data;
  struct BSTNode *left;
  struct BSTNode *right;
};

int getHeight(struct BSTNode *node){
    int balanceFactor;
    if(node==NULL){
       return -1;
    }else if(node->left== NULL && node->right==NULL){
        return 0;
    }
    else{
        int left_height=getHeight(node->left);
        int right_height=getHeight(node->right);
        if(left_height >= right_height){
            balanceFactor = left_height - right_height;
            left_height = left_height + 1;
        }
        else {
            balanceFactor = right_height - left_height;
            right_height = right_height + 1;
        }
        return balanceFactor;
    }
}
struct BSTNode *shiftLeft(struct BSTNode *node){
    struct BSTNode *NNode = node->right;
    struct BSTNode *LC = NNode->left;
    NNode->left = node;
    node->right =LC;
    return NNode;
}
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
  int balanceFactor = getHeight(node);
  if(balanceFactor>1){
      node = shiftLeft(node);
  }
  return node;
}
void PreOrder(struct BSTNode *node){
    if(node!=NULL ){
        printf("%d balance:%d\n",node->data,getHeight(node));
        PreOrder(node->left);
        PreOrder(node->right);
    }
}


int main() {
  struct BSTNode *Root = NULL;
  int choice;
  bool flag=true;
  do {
    printf("Menu:\n");
    printf("1. Insert\n");
    printf("2. Print\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        int value;
        printf("Enter the value to insert: ");
        scanf("%d", &value);
        Root = insert(Root, value);
        break;

      case 2:
        PreOrder(Root);
        break;

      case 3:
        printf("program finished\n");
        flag = false;
        break;

      default:
        printf("Invalid choice!\n");
        break;
    }
  } while (flag==true);

  return 0;
}