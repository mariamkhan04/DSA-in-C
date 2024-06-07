/*Expression tree to print infix expression usng in-order traversal*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ExprNode {
    char data;  // You can use char to represent operators or operands
    struct ExprNode* left;
    struct ExprNode* right;
};
// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to determine operator precedence
int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

// Function to check if operator1 has higher precedence than operator2
bool hasHigherPrecedence(char operator1, char operator2) {
    return precedence(operator1) > precedence(operator2);
}
// Function to insert nodes and construct an expression tree
struct ExprNode* insertExprNode(struct ExprNode* node, char value) {
    if (node == NULL) {
        struct ExprNode* temp = (struct ExprNode*)malloc(sizeof(struct ExprNode));
        temp->data = value;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }

    if (isOperator(value)) {
        if (hasHigherPrecedence(value, node->data) || (value == '^' && node->data == '^')) {
            struct ExprNode* newExprNode = (struct ExprNode*)malloc(sizeof(struct ExprNode));
            newExprNode->data = value;
            newExprNode->left = node->right;
            newExprNode->right = NULL;
            node->right = newExprNode;
        } else {
            node->left = insertExprNode(node->left, value);
        }
    } else {
        node->right = insertExprNode(node->right, value);
    }

    return node;
}
// Function to print the expression in infix notation
void printInfix(struct ExprNode* node) {
    if (node == NULL) {
        return;
    }

    if (isOperator(node->data)) {
        printf("(");
    }

    printInfix(node->left);
    printf("%c", node->data);
    printInfix(node->right);

    if (isOperator(node->data)) {
        printf(")");
    }
}

int main() {
    struct ExprNode* root = NULL;
    char expression[100];
    printf("Enter an arithmetic expression: ");
    scanf("%s", expression);

    // Process the expression string and construct the expression tree
    for (int i = 0; expression[i] != '\0'; i++) {
        root = insertExprNode(root, expression[i]);
    }

    printf("Infix expression: ");
    printInfix(root);

    // You can add evaluation functionality here

    return 0;
}