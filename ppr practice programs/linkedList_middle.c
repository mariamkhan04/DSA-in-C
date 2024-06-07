#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node
{
    int data;
    struct node *next;
} *start=NULL;
void insert(){
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    printf("Enter element: ");
    scanf("%d",&temp->data);
    temp->next=NULL;
    if (start==NULL)
    {
        start=temp;
    }else{
        struct node *curr=start;
        while (curr->next!=NULL)
        {
            curr=curr->next;
        }
        curr->next=temp;
    }
}
int print(){
    int length=0;
    struct node *curr=start;
    printf("Linked list is: \n");
    while (curr!=NULL)
    {
       printf("data: %d\n",curr->data);
       length++;
       curr=curr->next;
    }
    printf("\n");
    printf("the length of linked list is: %d\n",length);
}
int findMiddle(){
    struct node *curr=start;
    struct node *temp=start;
    while (curr->next!=NULL && curr->next->next!=NULL)
    {
        temp=temp->next;
        curr=curr->next->next;
    }
    if (curr->next==NULL)
    {
        printf("middle element is: %d\n",temp->data);
    }else{
        printf("middle elements are %d and %d\n",temp->data,temp->next->data);
    }
}
int main(){
    bool flag=true;
    int choice;
    while (flag)
    {
        printf("MENU\n1. insert\n2. print\n3. middle element\n4. exit\n");
        printf("enter your choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            insert();
            break;
        case 2:
            print();
            break;
        case 3:
            findMiddle();
            break;
        case 4:
            flag=false;
            break;
        default:
            printf("invalid choice\n");
            break;
        }
    }
    return 0;
}