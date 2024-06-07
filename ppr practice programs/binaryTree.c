#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node *createNode(struct Node *node,int value){
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->data=value;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
struct Node *insert(struct Node *node,int value){
    if (node==NULL){
        return createNode(node,value);
    }
    if (node->left==NULL){
        node->left=createNode(node->left,value);
    }else if(node->right==NULL){
        node->right=createNode(node->right,value);
    }else{
        node->left=insert(node->left,value);
    }
    return node;
}
//function to search a value in BST
bool search(struct Node *node,int value){
    if(node == NULL){
        printf("value %d not found!\n",value);
        return false;
    }
    if(node->data == value){
        printf("Value found\n");
        return true;
    }
    bool foundinleft=search(node->left,value);
    bool foundinRight=search(node->right,value);
    return foundinleft || foundinRight;

}

// function to print tree values using in-order traversal(in this values will be shown in ascending order)
void InOrder(struct Node *node){
    if(node != NULL){
        InOrder(node->left);
        printf("%d\n",node->data);
        InOrder(node->right);
    }
}
// function to print tree values using Pre-order traversal
void PreOrder(struct Node *node){
    if(node != NULL){
        printf("%d\n",node->data);
        PreOrder(node->left);
        PreOrder(node->right);
    }
}
// function to print tree values using post-order traversal
void PostOrder(struct Node *node){
    if(node != NULL){
        PostOrder(node->left);
        PostOrder(node->right);
        printf("%d\n",node->data);
    }
}
int main() {
    struct Node *Root = NULL;
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
            // case 6:
            //     printf("Enter the value to delete: ");
            //     scanf("%d", &value);
            //     Root = delete(Root, value);
            // break;
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