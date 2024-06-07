// stack operations push() and pop() using double Linked List
#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *next;
    struct Node *prev;
} *top = NULL;

void push(int value){
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->value = value;
    temp->prev = NULL;
    temp->next = top;
    if (top != NULL) {
        top->prev = temp;
    }

    top = temp;
}

void pop(){
    if(top == NULL){
        printf("Stack is empty");
        return;
    }
    else{
        printf("The value is: %d\n",top->value);
        struct Node *temp = top;
        top = top->next; 
        top->prev = NULL; 
        free(temp);
    }
}

int main(){
    int sizeOfStack,value;
    printf("Enter Size of stack: ");
    scanf("%d",&sizeOfStack);
    for (int i = 0; i < sizeOfStack; i++)
    {
        printf("Enter value: ");
        scanf("%d",&value);
        push(value);
    }
    for (int i = 0; i < sizeOfStack; i++)
    {
        pop();
    }
    return 0;
}