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
    int i, j;   //initializing two counters to track positions in input and output expressions
    i = j = 0;

    while (infix[i] != '\0') {//loop jab tk chalega jab tk end of expression na phonch jaye
        if (infix[i] == ' ' || infix[i] == '\t') { //if we encounter spaces or tabs we will skip them
            i++;
        } else if (isalnum(infix[i])) { //if we encounter an alphanumeric char(operand) we will add it to postfixs
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

int main() {
    char infix[100], postfix[100];
    printf("Enter an infix expression: ");
    gets(infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}