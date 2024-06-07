#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct Node
{
    int data;
    struct Node *next;
} *start=NULL;

void insert(int value){
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->data=value;
    temp->next=NULL;
    if (start==NULL)
    {
        start=temp;
    }else{
        struct Node *curr=start;
        while (curr->next!=NULL)
        {
            curr=curr->next;
        }
        curr->next=temp;
    }
}
void search(int tosearch){
    struct Node *curr=start;
    while (curr!=NULL)
    {
        if (tosearch==curr->data)
        {
            printf("id %d found\n",curr->data);
            return;
        }
        curr=curr->next;
    }
    if (curr==NULL)
    {
        printf("Element not found\n");
    }
}
void swapNodes(int id1, int id2) {
    // to find both nodes
    struct Node *prev1 = NULL;
    struct Node *curr1 = start;
    while (curr1 != NULL && curr1->data != id1) {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    struct Node *prev2 = NULL;
    struct Node *curr2 = start;
    while (curr2 != NULL && curr2->data != id2) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    // to swap nodes
    if (prev1 != NULL) {
        prev1->next = curr2;
    } else {
        start = curr2;
    }

    if (prev2 != NULL) {
        prev2->next = curr1;
    } else {
        start = curr1;
    }

    if (curr1 == NULL || curr2 == NULL) {
        printf("id1 or id2 or both ids don't exist\n");
        return;
    }
    struct Node *temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;

    printf("Nodes with ids %d and %d are swapped\n", id1, id2);
}
void deleteNode(int value){
    int found=0;
    struct Node *curr=start;
    if (value==curr->data)
    {
        start=start->next;
        found=1;
        free(curr);
    }else{
        struct Node *prev=start;
        curr=start->next;
        while (curr!=NULL)
        {
            if (value==curr->data)
            {
                prev->next=curr->next;
                found=1;
                free(curr);
                break;
            }else{
                prev=prev->next;
                curr=curr->next;
            }
        }
    }
    if (found==0){
        printf("elemnet not found\n");
    }
}
void deleteAll(){
    struct Node *curr=start;
    while(curr!=NULL){
        struct Node *temp=curr;
        curr=curr->next;
        free(temp);
    }
    start=NULL;
    printf("all elements deleted\n");
}
void print(){
    struct Node *curr=start;
    while (curr!=NULL)
    {
        printf("%d ",curr->data);
        curr=curr->next;
    }
    printf("\n");
}
int main(){
    int choice,value,toSearch,id1,id2;
    bool flag=true;
    while (flag)
    {
        printf("MENU\n1. insert\n2. search\n3. swap\n4. delete\n5. deleteAll\n6. print\n7. exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("Enter value you want to insert: ");
            scanf("%d",&value);
            insert(value);
            break;
        case 2:
            printf("enter value to search: ");
            scanf("%d",&toSearch);
            search(toSearch);
            break;
        case 3:
            printf("value 1 to search: ");
            scanf("%d",&id1);
            printf("value 2 to search: ");
            scanf("%d",&id2);
            swapNodes(id1,id2);
            break;
        case 4:
            printf("Enter value want to delete: ");
            scanf("%d",&value);
            deleteNode(value);
            break;
        case 5:
            deleteAll();
            break;
        case 6:
            print();
            break;
        case 7:
            printf("program finished\n");
            flag=false;
            break;
        default:
            printf("inavlid choice\n");
            break;
        }
    }
    return 0;
}