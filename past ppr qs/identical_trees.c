#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct BSTNode{
    char data[100];
    struct BSTNode* left;
    struct BSTNode* right;

};
struct BSTNode* createNewNode(const char* data) {
    struct BSTNode* newNode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    strcpy(newNode->data, data); // Copy the string data
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct BSTNode* insert(struct BSTNode* node, const char* data) {
    if (node == NULL) {
        return createNewNode(data);
    }
    int cmp = strcmp(data, node->data);
    if (cmp > 0) {
        node->right = insert(node->right, data);
    } else if (cmp < 0) {
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
    root1 = insert(root1,"emaan");
    root1 = insert(root1,"tahir");
    root1 = insert(root1,"khan");
    root1 = insert(root1,"yousufzai");
    root1 = insert(root1,"pathan");
    
    
    printf("The tree is :\n");
    inOrder(root1); 
    struct BSTNode* root2= NULL;
    root2= insert(root2,"tahir");
    root2 = insert(root2,"khan");
    root2 = insert(root2,"pathan");
    root2 = insert(root2,"yousuf");
    root2 = insert(root2,"aiman");
    
    printf("The Other tree is :\n");
    inOrder(root2); 
    // Print the elements of the tree
    if (isIdentical(root1,root2)&&hasSameStructure(root1,root2))
    {
        printf("Both BSTs are identical and has same structure");
    }else if (isIdentical(root1,root2)&&!hasSameStructure(root1,root2))
    {
        printf("Both BSTs are identical and but has no same structure");
    }else
    {
        printf("Both BSTs are not identical and but has same structure");
    }

    if (areMirrors(root1,root2))
    {
        printf("\nBoth BSTs are mirror");
    }else
    {
        printf("\nBoth BSTs are not mirror");
    }
    

    return 0;
}

