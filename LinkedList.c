#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node{
    int id;
    int marks;
    struct Node *next; //holds the address of next node
} *start= NULL; //initially the list will be null/empty (global variable declaration)
//to insert a node
void insert(){
    //dyanmically allocating memory 
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    printf("Enter id: ");
    scanf("%d",&temp->id);
    printf("Enter Marks: ");
    scanf("%d",&temp->marks);
    temp->next= NULL;
    if(start == NULL){//if start is null update start
        start=temp;
    }
    else{
        struct Node *curr=start;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next=temp;
    }
}

void printLinkedList(){
    struct Node *curr = start;
    printf("Linked List is: \n");
    while (curr!=NULL)
    {
        printf("ID is: %d\n",curr->id);
        printf("Marks are: %d\n",curr->marks);
        curr=curr->next;
    }
}

// to search the element in list
void search(){
    int toSearchId;
    printf("Enter the ID you want to find: ");
    scanf("%d",&toSearchId);
    struct Node *curr=start;//curr points to start
    while(curr != NULL){
        if(toSearchId == curr->id){ 
            printf("Id found: %d\nMarks at Id: %d\n",curr->id,curr->marks);
            break;
        }
        curr=curr->next;
    }
    if(curr==NULL){
        printf("Element not found");
    }
}

// to delete a single node (to delete we have to first search then delete)
void delete(){
    struct Node *curr=start;
    int toDeleteId;
    printf("Enter id : ");
    scanf("%d",&toDeleteId);
    //if you want to delete first Node 
    if(toDeleteId==start->id){
        start=start->next; //update start
        free(curr);//free is used to deallocate memory
    }
    else{//if the node to be deleted is not first you have to maintain prev with respect to curr
        struct Node *prev = start;
        curr = start->next;
        while(curr != NULL){
            if(curr->id == toDeleteId){
                prev->next = curr->next;
                free(curr);
                break; 
            }
            else{
                prev = prev->next;
                curr = curr->next;
            }
        }
        if(curr == NULL){
            printf("Element not found");
        }
    }
}

// to delete whole list
void deleteAll(){
    struct Node *curr=start;
    while(curr != NULL){
        struct Node *temp=curr;
        curr = curr->next;
        free(temp);
    }
    start = NULL;
    printf("All Nodes deleted\n");
}

int main(){
    int choice;
    bool flag= true;
    while(flag == true){
        printf("\tOptions\t\n");
        printf("1. Insert\n");
        printf("2. Print\n");
        printf("3. Search\n");
        printf("4. DeleteNode\n");
        printf("5. DeleteAll\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                insert();    
            break;
            case 2:
                printLinkedList();
            break;
            case 3:
                search();
            break;
            case 4:
                delete();
            break;
            case 5:
                deleteAll();
            break;
            case 6:
                printf("Program Finished");
                flag = false;
            break;
            default:
                printf("Enter valid choice!");
        }
    }
    return 0;
}