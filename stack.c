// stack push and pop using single linked list
#include<stdio.h>
#include<stdlib.h>
struct Node{
    int value;
    struct Node *next;
} *top = NULL;

void push(int value){
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->value= value;
    temp->next = top; // link create krne keliye 
    top = temp;    
}
void pop(){
    if(top == NULL){    //underflow condition check
        printf("Stack is empty");
        return;
    }
    else{
        printf("The value is %d\n",top->value);
        struct Node *temp = top;
        top = top->next;
        free(temp);
    }
}
//to print top value 
void peek(){
    if (top==NULL)
    {
        printf("Stack is empty\n");
    }else{
        printf("Top element is %d\n",top->value);
    }
}
int main(){
    int value,choice;
    while (1)
    {
        printf("Menu\n1. push\n2. pop\n3. peek\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d",&value);
            push(value);
            break;
        case 2:
            pop();
            break;
        case 3:
            peek();
            break;
        case 4:
            exit(1);
            break;
        default:
            printf("invalid choice\n");
            break;
        }
    }
    
    
   
        push(value);
        peek();
        pop();
}