#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct Queue
{
    char data;
    struct Queue *next;
};
struct Queue *front=NULL;
struct Queue *rear=NULL;
void EnQueue(char data){
    struct Queue *temp=(struct Queue *)malloc(sizeof(struct Queue));
    temp->data=data;
    temp->next=NULL;
    if (front==NULL){
        front=temp;
        rear=temp;
    }else{
        rear->next=temp;
        rear=temp;
    }
}
void deQueue(){
    if(front==NULL){
        printf("Queue is empty\n");
    }else{
        printf("value is: %c\n",front->data);
        struct Queue *temp=front;
        front=front->next;
        free(temp);
    }
    if (front==NULL)
    {
        rear=NULL;
    }
}
int main(){
    char data;
    int choice;
    bool flag=true;
    while (flag)
    {
        printf("Menu\n1.EnQueue\n2.deQueue\n3.exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter data: ");
                scanf(" %c",&data);
                EnQueue(data);
                break;
            case 2:
                deQueue();
                break;
            case 3:
                printf("Program ended\n");
                flag=false;
                break;
            default:
                printf("invalid choice\n");
        }
    }
    return 0;
}