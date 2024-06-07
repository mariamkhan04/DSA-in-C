#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure for the expression tree node
struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '<' || ch == '>' || ch == '~' || ch == '&' || ch == '|');
}

// Function to create a new expression tree node
struct TreeNode *createNode(char data) {
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to build an expression tree from a postfix expression
struct TreeNode *buildExpressionTree(char *postfix) {
    struct TreeNode *root = NULL;
    struct TreeNode *tempStack[100]; // Assuming a maximum of 100 nodes
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];

        if (!isOperator(token)) {
            struct TreeNode *node = createNode(token);
            tempStack[++top] = node;
        } else {
            struct TreeNode *operator = createNode(token);
            operator->right = tempStack[top--];
            operator->left = tempStack[top--];
            tempStack[++top] = operator;
        }
    }

    if (top == 0) {
        root = tempStack[0];
    } else {
        printf("Error: Invalid postfix expression\n");
    }

    return root;
}

// Function to perform an in-order traversal of the expression tree
void inOrderTraversal(struct TreeNode *root) {
    if (root) {
        inOrderTraversal(root->left);
        printf("%c", root->data);
        inOrderTraversal(root->right);
    }
}

int main() {
    char postfix[100];
    printf("Enter a postfix expression: ");
    gets(postfix);

    struct TreeNode *expressionTree = buildExpressionTree(postfix);

    printf("In-order traversal of the expression tree: ");
    inOrderTraversal(expressionTree);

    return 0;
}
