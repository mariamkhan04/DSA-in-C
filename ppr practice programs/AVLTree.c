#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct BSTNode{
    int value;
    struct BSTNode *left;
    struct BSTNode *right;
};
int getHeight(struct BSTNode *node){
    if(node==NULL){
        return -1;
    }
    int leftHeight=getHeight(node->left);
    int rightHeight=getHeight(node->right);
    return (leftHeight>rightHeight?leftHeight:rightHeight)+1;
}
int getBalance(struct BSTNode *node){
    if (node==NULL){
        return 0;
    }
    return getHeight(node->left)-getHeight(node->right);
}
struct BSTNode *shiftLeft(struct BSTNode *node){
    struct BSTNode *newNode=node->right;
    struct BSTNode *T2=newNode->left;

    newNode->left=node;
    node->right=T2;

    return newNode;
}
struct BSTNode *shiftRight(struct BSTNode *node){
    struct BSTNode *newNode=node->left;
    struct BSTNode *T2=newNode->right;

    newNode->right=node;
    node->left=T2;

    return newNode;
}
struct BSTNode *insert(struct BSTNode *node,int value){
    if (node==NULL){
        struct BSTNode *temp=(struct BSTNode *)malloc(sizeof(struct BSTNode));
        temp->value=value;
        temp->left=NULL;
        temp->right=NULL;
        return temp;
    }
    if(value < node->value){
        node->left=insert(node->left,value);
    }else{
        node->right=insert(node->right,value);
    }

    int balanceFactor= getBalance(node);

    if(balanceFactor > 1){
        if (value < node->left->value)
        {
            //l-l condition
            node=shiftRight(node);
        }else{
            //l-r condition
            node->left=shiftLeft(node->left);
            node=shiftRight(node);
        }
    }else if(balanceFactor < -1){
        if (value > node->right->value)
        {
            //r-r condition
            node=shiftLeft(node);
        }else{
            //r-l condition
            node->right=shiftRight(node->right);
            node=shiftLeft(node);
        }
    }
    return node;
}
void PreOrder(struct BSTNode *node){
    if(node!=NULL){
        printf("%d balnace %d\n",node->value,getBalance(node));
        PreOrder(node->left);
        PreOrder(node->right);
    }
}
int main() {
    struct BSTNode *Root = NULL;
    int choice;
    int value;
    bool flag = true;

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
                PreOrder(Root);
                break;

            case 3:
                printf("Program finished\n");
                flag = false;
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (flag == true);

    return 0;
}
