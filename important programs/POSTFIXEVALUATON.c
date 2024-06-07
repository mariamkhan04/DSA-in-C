#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    int value;
    struct Node* next;
};

typedef struct Node Node;

Node* stack = NULL;

// Function to push a value onto the stack
void push(int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->value = value;
    temp->next = stack;
    stack = temp;
}

// Function to pop a value from the stack
int pop() {
    if (stack == NULL) {
        printf("Error: Invalid postfix expression\n");
        exit(1);
    } else {
        Node* temp = stack;
        int poppedValue = temp->value;
        stack = stack->next;
        free(temp);
        return poppedValue;
    }
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to perform arithmetic operations
int applyOperator(char operator, int operand1, int operand2) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                printf("Error: Division by zero\n");
                exit(1);
            }
            return operand1 / operand2;
        case '^':
            return (int)pow(operand1, operand2);
        default:
            printf("Error: Invalid operator %c\n", operator);
            exit(1);
    }
}

// Function to evaluate a postfix expression
int evaluatePostfix(char *postfix) {
    int i = 0;
    while (postfix[i] != '\0') {
        if (isalpha(postfix[i])) {
            char variable = postfix[i];
            int value;
            printf("Enter the value for operand %c: ", variable);
            scanf("%d", &value);
            push(value);
            i++;
        } else if (isdigit(postfix[i])) {
            int value = 0;
            while (isdigit(postfix[i])) {
                value = value * 10 + (postfix[i] - '0');
                i++;
            }
            push(value);
        } else if (isOperator(postfix[i])) {
            int operand2 = pop();
            int operand1 = pop();
            char operator = postfix[i];
            int result = applyOperator(operator, operand1, operand2);
            push(result);
            i++;
        } else {
            i++; // Skip whitespace or other characters
        }
    }
    int finalResult = pop();
    if (stack != NULL) {
        printf("Error: Invalid postfix expression\n");
        exit(1);
    }
    return finalResult;
}

int main() {
    char postfix[100];
    printf("Enter a postfix expression: ");
    fgets(postfix, sizeof(postfix), stdin);

    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}