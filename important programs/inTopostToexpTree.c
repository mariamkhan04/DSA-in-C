#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Include the ctype.h header for isalnum
int precedence(char c) {
    switch (c) {
        case '*':
        case '/':
            return 5;
        case '+':
        case '-':
            return 4;
        case '<':
        case '>':
        case '~':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        default:
            return 0;
    }
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '<' || ch == '>' || ch == '~' || ch == '&' || ch == '|');
}

struct Node {
    char value;
    struct Node *next;
} *top = NULL;

void push(char value) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->value = value;
    temp->next = top;
    top = temp;
}

char pop() {
    if (top == NULL) {
        return 0;
    } else {
        struct Node *temp = top;
        char poppedValue = temp->value;
        top = top->next;
        free(temp);
        return poppedValue;
    }
}

char peek() {
    if (top == NULL) {
        return 0;
    } else {
        return top->value;
    }
}

void infixToPostfix(char *infix, char *postfix) {
    int i, j;
    i = j = 0;

    while (infix[i] != '\0') {
        if (infix[i] == ' ' || infix[i] == '\t') {
            i++;
        } else if (isalnum(infix[i])) {
            postfix[j++] = infix[i++];
        } else if (isOperator(infix[i])) {
            while (precedence(infix[i]) <= precedence(peek()) && peek() != '(') {
                postfix[j++] = pop();
            }
            push(infix[i++]);
        } else if (infix[i] == '(') {
            push(infix[i++]);
        } else if (infix[i] == ')') {
            while (peek() != '(') {
                postfix[j++] = pop();
            }
            pop();
            i++;
        }
    }

    while (peek() != 0) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}
// Structure for the expression tree node
struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
};
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

        if (!isOperator(postfix[i])) {
            struct TreeNode *node = createNode(postfix[i]);
            tempStack[++top] = node;
        } else { //If the current character token is an operator, it creates a new node for the operator and connects it to the two nodes on the stack 
            struct TreeNode *operator = createNode(postfix[i]);
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
    char infix[100], postfix[100];
    printf("Enter an infix expression: ");
    gets(infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    struct TreeNode *expressionTree = buildExpressionTree(postfix);

    printf("In-order traversal of the expression tree: ");
    inOrderTraversal(expressionTree);

    return 0;
}
// Enter an infix expression: a*(b+c-d)/x<5+a&(c~e|a+b>x+y)
// Postfix expression: abc+d-*x/5a+<ce~ab+xy+>|&
// In-order traversal of the expression tree: a*b+c-d/x<5+a&c~e|a+b>x+y