#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node *insert(struct Node *node,int value){
    if(node==NULL){
        struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
        temp->data=value;
        temp->left=NULL;
        temp->right=NULL;
        return temp;
    }else if(value<node->data){
        node->left=insert(node->left,value);
    }else{
        node->right=insert(node->right,value);
    }
    return node;
}
void search(struct Node *node,int value){
    if(node==NULL){
        printf("%d value not found\n",value);
    }else if(node->data==value){
        printf("%d value found\n",value);
    }else if(value<node->data){
        search(node->left,value);
    }else{
        search(node->right,value);
    }
}
// Function to delete a node
struct Node* delete(struct Node *node, int value) {
  if (node == NULL) {
    printf("Value not found");
    return NULL; //if node is null return null address
  }

  if (value < node->data) { //if value if less than current node value go to left and recursively call function, same if value is greater than current node value go to right and recursively call function 
    node->left = delete(node->left, value);
  } else if (value > node->data) {
    node->right = delete(node->right, value);
  } else {
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
  }

  return node;
}

void inorder(struct Node *node){
    if(node != NULL){
        inorder(node->left);
        printf("%d\t",node->data);
        inorder(node->right);
    }
}
int main(){
    struct Node *Root=NULL;
    int choice,value;
    bool flag=true;
    while(flag){
        printf("MENU: \n1. Insert\n2. Search\n3. Delete\n4. Print\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d",&value);
            Root=insert(Root,value);
            break;
        case 2:
            printf("Enter value to search: ");
            scanf("%d",&value);
            search(Root,value);
            break;
        case 3:
            printf("Enter value to delete: ");
            scanf("%d",&value);
            Root=delete(Root,value);
            break;
        case 4:
            inorder(Root);
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