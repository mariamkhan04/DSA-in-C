#include<stdio.h>
#include<stdlib.h>

struct Node{
    char data;
    struct Node *next;
} *top = NULL;

void push(char data){
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->data= data;
    temp->next = top;
    top = temp; 
}
void pop(){
    if(top == NULL){
        printf("Stack is empty");
        return;
    }
    else{
        printf("%d",top->data);
        struct Node *temp = top;
        top = top->next;
        free(temp);
    }
}

// Function to convert an infix expression to postfix expression
char *postfix(char *exp) {
    // Create a stack to store operators
    struct Node *stack = NULL;

    // Create an output string to store the postfix expression
    char *output = (char *)malloc(sizeof(char) * (strlen(exp) + 1));
    int i;
    // Iterate over the infix expression
    for (i = 0; i < strlen(exp); i++) {
        char ch = exp[i];

        // If the character is an operand, add it to the output string
        if (!isOperator(ch)) {
            output[i] = ch;
        } else {
        // While the stack is not empty and the top operator has a higher or equal
        // precedence than the current operator, pop the operator from the stack and
        // append it to the output string
        while (stack != NULL && getPrecedence(ch) <= getPrecedence(stack->data)) {
            output[i++] = stack->data;
            stack = stack->next;
        }

        // Push the current operator to the stack
        push(ch);
        }
    }

    // Pop all remaining operators from the stack and append them to the output string
    while (stack != NULL) {
        output[i++] = stack->data;
        stack = stack->next;
    }

    // Add a terminating character to the output string
    output[i] = '\0';

    return output;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '^') {
        return 3;
    } else {
        return 0;
    }
}

int main() {
    char expression[100];

    // Get the infix expression from the user
    printf("Enter an infix expression: ");
    scanf("%s", expression);

    // Convert the infix expression to postfix expression
    char *postfixExpression = postfix(expression);

    // Print the postfix expression
    printf("The postfix expression is: %s\n", postfixExpression);

    return 0;
}
