#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct Node{
    int data;
    struct Node *next;
    struct Node *prev;
} *start=NULL;
void insert(int value){
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->data=value;
    temp->next=NULL;
    temp->prev=NULL;
    if(start==NULL){
        start=temp;
    }else{
        struct Node *curr=start;
        while (curr->next!=NULL)
        {
            curr=curr->next;
        }
        curr->next=temp;
        temp->prev=curr;
    }
}
void print(){
    struct Node *curr=start;
    if (curr==NULL)
    {
        printf("graph is empty\n");
        return;
    }
    while (curr!=NULL)
    {
        printf("%d\n",curr->data);
        curr=curr->next;
    }
}
int main(){
    int choice,value;
    bool flag=true;
    while (flag)
    {
        printf("Menu\n1. insert value\n2. print\n3. swap nodes\n4. exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d",&value);
            insert(value);
            break;
        case 2:
            print();
            break;
        case 4:
            printf("Program finished\n");
            flag=false;
            break;
        default:
            printf("invalid choice\n");
            break;
        }
    }
    
}