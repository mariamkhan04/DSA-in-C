#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct BSTNode{
    char data[100];
    struct BSTNode *left;
    struct BSTNode *right;
};
struct BSTNode *createNewNode(char *data) {
    struct BSTNode *temp = (struct BSTNode *)malloc(sizeof(struct BSTNode));
    strcpy(temp->data, data); // Copy the string data
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
struct BSTNode *insert(struct BSTNode* node, char* data) {
    if (node == NULL) {
        return createNewNode(data);
    }
    int cmp = strcmp(data, node->data); //if strings are equal
    if (cmp > 0) {  //if the first non-matching character in data is greater (in ASCII) than that of node->data.
        node->right = insert(node->right, data);
    } else if (cmp < 0) {   //if the first non-matching character in str1 is lower (in ASCII) than that of str2.
        node->left = insert(node->left, data);
    }  
      return node;
}
void inOrder(struct BSTNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%s\t", root->data);
        inOrder(root->right);
    }
}
bool isIdentical(struct BSTNode* root1, struct BSTNode* root2) {
    if (root1 == NULL && root2 == NULL) {
        return true;
    } else if (root1 == NULL || root2 == NULL) {
        return false;
    } else {
        int cmp = strcmp(root1->data, root2->data);
        return (cmp == 0) && isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right);
    }
}
bool hasSameStructure(struct BSTNode* root1, struct BSTNode* root2) {
    if (root1 == NULL && root2 == NULL) {
        return true;
    } else if (root1 == NULL || root2 == NULL) {
        return false;
    } else {
        bool leftStructure = hasSameStructure(root1->left, root2->left);
        bool rightStructure = hasSameStructure(root1->right, root2->right);
        return leftStructure && rightStructure;
    }
}
bool areMirrors(struct BSTNode* root1, struct BSTNode* root2) {
    if (root1 == NULL && root2 == NULL) {
        return true;
    } else if (root1 == NULL || root2 == NULL) {
        return false;
    } else {
        int cmp = strcmp(root1->data, root2->data);
        return (cmp == 0) && areMirrors(root1->left, root2->right) && areMirrors(root1->right, root2->left);
    }
}
int main()
{
    struct BSTNode* root1 = NULL;
    struct BSTNode* root2= NULL;
    int choice;
    bool flag=true;
    char str[100];
    while(flag){
        printf("Menu: \n1. insert tree 1\n2. insert tree 2\n3. isidentical?\n4. samestructure?\n5. mirror?\n6. print tree 1\n7. print tree 2\n8. exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("Enter the string: ");
            scanf("%s",&str);
            root1=insert(root1,str);
            break;
        case 2:
            printf("Enter the string: ");
            scanf("%s",&str);
            root2=insert(root2,str);
            break;
        case 3:
            printf("check if both trees are identical?\n");
            if (isIdentical(root1,root2)){
                printf("Both trees are identical/ have same data\n");
            }else{
                printf("both trees are not identical.\n");
            }
            break;
        case 4:
            printf("check if both trees have same structure?\n");
            if (hasSameStructure(root1,root2)){
                printf("Both trees have same structure\n");
            }else{
                printf("both trees don't have same structure.\n");
            }
            break;
        case 5:
            printf("check if both bsts are mirror?\n");
            if(areMirrors(root1,root2)){
                printf("both bsts are mirrors\n");
            }else{
                printf("both bsts are not mirrors\n");
            }
            break;
        case 6:
            inOrder(root1);
            break;
        case 7:
            inOrder(root2);
            break;
        case 8:
            flag=false;
            break;
        default:
            break;
        }
    }
    return 0;
}