#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Stack {
  char *data;
  int top;
  int capacity;
};

struct Stack *createStack(int capacity) {
  struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
  if (stack == NULL) {
    return NULL;
  }

  stack->data = (char *)malloc(sizeof(char) * capacity);
  if (stack->data == NULL) {
    return NULL;
  }

  stack->top = -1;
  stack->capacity = capacity;

  return stack;
}

void push(struct Stack *stack, char c) {
  if (stack->top == stack->capacity - 1) {
    return;
  }

  stack->top++;
  stack->data[stack->top] = c;
}

char pop(struct Stack *stack) {
  if (stack->top == -1) {
    return '\0';
  }

  char c = stack->data[stack->top];
  stack->top--;

  return c;
}

int isEmpty(struct Stack *stack) {
  return stack->top == -1;
}

int precedence(char c) {
  switch (c) {
    case '*':
    case '/':
        return 6;
    case '+':
    case '-':
        return 5;
    case '<':
    case '>':
        return 4;
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

char *infixToPostfix(char *infix) {
  struct Stack *stack = createStack(strlen(infix));
  if (stack == NULL) {
    return NULL;
  }

  char *postfix = (char *)malloc(sizeof(char) * (strlen(infix) + 1));
  if (postfix == NULL) {
    return NULL;
  }

  int i = 0;
  int j = 0;
  while (infix[i] != '\0') {
    char c = infix[i];

    if (c == '(') {
      push(stack, c);
    } else if (c == ')') {
      while (!isEmpty(stack) && stack->data[stack->top] != '(') {
        postfix[j++] = pop(stack);
      }

      if (!isEmpty(stack) && stack->data[stack->top] == '(') {
        pop(stack);
      }
    } else if (c >= 'a' && c <= 'z') {
      postfix[j++] = c;
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '&' || c == '|' || c == '~' || c == '<' || c == '>') {
      while (!isEmpty(stack) && precedence(stack->data[stack->top]) >= precedence(c)) {
        postfix[j++] = pop(stack);
      }

      push(stack, c);
    }

    i++;
  }

  while (!isEmpty(stack)) {
    postfix[j++] = pop(stack);
  }

  postfix[j] = '\0';

  free(stack);
  return postfix;
}

int main() {
  char *infix = "a*(b+c-d)/x<n+a&(c~e|a+b>x+y)";
  char *postfix = infixToPostfix(infix);

  if (postfix == NULL) {
    printf("Error: Converting infix to postfix failed.\n");
    return 1;
  }

  printf("The postfix expression is: %s\n",postfix);
  return 0;
}
