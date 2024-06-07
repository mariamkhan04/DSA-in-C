#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct Stack
{
    char data;
    struct Stack *next;
} *top=NULL;
void push(char data){
    struct Stack *temp=(struct Stack *)malloc(sizeof(struct Stack));
    temp->data=data;
    temp->next=top;
    top=temp;
}
void pop(){
    if (top==NULL)
    {
        printf("Stack underflow");
        return;
    }else{
        printf("the value is: %c\n",top->data);
        struct Stack *temp=top;
        top=top->next;
        free(temp);
    }
}
void peek(){
    if (top==NULL)
    {
        printf("Stack is empty\n");
    }else{
        printf("The element at top is: %c\n",top->data);
    }   
}

int main(){
    char data;
    int choice;
    bool flag=true;
    while (flag)
    {
        printf("Menu\n1.push\n2.pop\n3.peek\n4.exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter data: ");
                scanf(" %c",&data);
                push(data);
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                printf("Program ended\n");
                flag=false;
                break;
            default:
                printf("invalid choice\n");
        }
    }
    return 0;
}