#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct BSTNode{
    int data;
    struct BSTNode *left;   // to point left child
    struct BSTNode *right;  //to point right child
};
//Function to insert a value in BST
struct BSTNode* insert(struct BSTNode *node,int value){
    if(node==NULL){ //if tree is empty then we allocate mem using malloc for node and then make its left and right subchilds null and return address of node
        struct BSTNode *temp = (struct BSTNode *)malloc(sizeof(struct BSTNode));
        temp->data = value;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    if(value > node->data){ // if tree is not empty and value that we want to insert is greater than value of node than recursively update node's right child
        node->right = insert(node->right,value);
    }else{ // if tree is not empty and value that we want to insert is lesser than value of node than recursively update node's left child
        node->left = insert(node->left,value);
    }
    return node;
}
//function to search a value in BST
void search(struct BSTNode *node,int value){
    if(node == NULL){
        printf("value %d not found!\n",value);
        return;
    }
    if(node->data == value){
        printf("Value found\n");
    }else if(value < node->data){
        search(node->left,value);
    }else{
        search(node->right,value);
    }
}
// Function to delete a node
struct BSTNode* delete(struct BSTNode *node, int value) {
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
      struct BSTNode *temp = node->right;
      free(node);
      return temp;
    } else if (node->right == NULL) {
      struct BSTNode *temp = node->left;
      free(node);
      return temp;
    }

    // Node has both children
    struct BSTNode *smallest = node->right;
    while (smallest->left != NULL) {
      smallest = smallest->left;
    }

    node->data = smallest->data;
    node->right = delete(node->right, smallest->data);
  }

  return node;
}

// function to print tree values using in-order traversal(in this values will be shown in ascending order)
void InOrder(struct BSTNode *node){
    if(node != NULL){
        InOrder(node->left);
        printf("%d\n",node->data);
        InOrder(node->right);
    }
}
// function to print tree values using Pre-order traversal
void PreOrder(struct BSTNode *node){
    if(node != NULL){
        printf("%d\n",node->data);
        PreOrder(node->left);
        PreOrder(node->right);
    }
}
// function to print tree values using post-order traversal
void PostOrder(struct BSTNode *node){
    if(node != NULL){
        PostOrder(node->left);
        PostOrder(node->right);
        printf("%d\n",node->data);
    }
}
int main() {
    struct BSTNode *Root = NULL;
    int choice;
    int value;
    int toSearch;
    bool flag=true;
    do {
        printf("Menu:\n");
        printf("1. Insert\n");
        printf("2. In-order Traversal\n");
        printf("3. Pre-order Traversal\n");
        printf("4. Post-order Traversal\n");
        printf("5. Search\n");
        printf("6. Delete\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                Root = insert(Root, value);
            break;
            case 2:
                InOrder(Root);
            break;
            case 3:
                PreOrder(Root);
            break;
            case 4:
                PostOrder(Root);
            break;
            case 5:
                printf("Enter the value to search: ");
                scanf("%d",&toSearch);
                search(Root,toSearch);
            break;
            case 6:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                Root = delete(Root, value);
            break;
            case 7:
                printf("Program finished!");
                flag=false;
            break;
            default:
                printf("Invalid choice!\n");
            break;
        }
    }while (flag != false);
    return 0;
}