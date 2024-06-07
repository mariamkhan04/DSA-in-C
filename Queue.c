#include<stdio.h>
#include<stdlib.h>
struct Node{
    int value;
    struct Node *next;
} ;
struct Node *front = NULL;
struct Node *rear = NULL;

void EnQueue(int value){
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->value= value;
    temp->next = NULL;
    if (front == NULL) {
        front = temp;
        rear = temp;
    }
    else {
        rear->next = temp;
        rear = temp;
    }
}    
int dequeue() {
    if (front == NULL) {
        printf("Queue is empty");
        return -1;
    }

    printf("The value is: %d\n",front->value);
    struct Node *temp = front;
    front = front->next;
    free(temp);

    if (front == NULL) {
        rear = NULL;
    }
}

int main(){
    int sizeOfQueue,value;
    printf("Enter size of Queue: ");
    scanf("%d",&sizeOfQueue);
    for(int i=0 ; i < sizeOfQueue; i++){
        printf("Enter value: ");
        scanf("%d",&value);
        EnQueue(value);
    }
    for(int i=0; i < sizeOfQueue; i++){
        dequeue();
    }
}