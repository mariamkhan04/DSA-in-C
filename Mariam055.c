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
void swap(int n1,int n2){
    struct Node *prev1=NULL;
    struct Node *curr1=start;
    if (curr1->data==n1)
    {
        curr1=start;
    }else{
        struct Node *temp=start->next;
        while (temp!=NULL)
        {
            if (temp->data==n1)
            {
                curr1=temp;
                prev1=temp->prev;
            }
            temp=temp->next;
        }
        if (temp==NULL)
        {
            printf("node 1 not found\n");
        }
    }
    struct Node *prev2=NULL;
    struct Node *curr2=start;
    if (curr2->data==n2)
    {
        curr2=start;
    }else{
        struct Node *temp=start->next;
        while (temp!=NULL)
        {
            if (temp->data==n1)
            {
                curr2=temp;
                prev2=temp->prev;
            }
            temp=temp->next;
        }
        if (temp==NULL)
        {
            printf("node 2 not found\n");
        }
    }

    if (prev1==NULL)
    {
        curr2->prev=prev1;
        prev2=prev1;
    }else{
        curr2->prev=curr1->prev;
        prev2=curr2->prev;
    }
    if (prev2==NULL)
    {
        curr1->prev=prev2;
        prev1=prev2;
    }else{
        curr1->prev=curr2->prev;
        prev1=curr1->prev;
    }
    int temp=curr2->next;
    
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
        case 3:
            int n1,n2;
            printf("Enter node 1: ");
            scanf("%d",&n1);
            printf("Enter node 2: ");
            scanf("%d",&n2);
            swap(n1,n2);
            braek;
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