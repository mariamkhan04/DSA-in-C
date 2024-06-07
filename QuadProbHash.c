#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define size 6
int hashFunc(int keyVal){
    return (keyVal%size);
}
void insert(int arr[],int keyVal){
    int ind=hashFunc(keyVal);
    if (arr[ind]==-1)
    {
        arr[ind]=keyVal;
        return;
    }else{
        for (int i = 1; i < size; i++)
        {
            int newInd=(ind+(i*i))%size;
            if (arr[newInd]==-1)
            {
                arr[newInd]=keyVal;
                return;
            }
        }
    }
}
int search(int arr[], int keyVal) {
    int ind = hashFunc(keyVal);
    for (int i = 0; i < size; i++) {
        int currentInd = (ind + (i*i)) % size;
        if (arr[currentInd] == keyVal) {
            return currentInd;
        }
        // If the slot is empty, break since the key is not in the hash table
        if (arr[currentInd] == -1) {
            break;
        }
    }
    return -1; // Key not found
}
void deleteKey(int arr[], int keyVal) {
    int ind = search(arr, keyVal);
    if (ind != -1) {
        arr[ind] = -1; // Mark the slot as empty
        printf("Key %d deleted from index %d\n", keyVal, ind);
    } else {
        printf("Key %d not found for deletion\n", keyVal);
    }
}
void print(int arr[]){
    for (int i = 0; i < size; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int main(){
    int choice,keyVal;
    bool flag=true;
    int arr[10];
    for (int i = 0; i < size; i++)
    {
        arr[i]=-1;
    }
    while (flag)
    {
        printf("MENU\n1. Insert\n2. Print\n3. Search\n4. Delete\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("enter key value: ");
            scanf("%d",&keyVal);
            insert(arr,keyVal);
            break;
        case 2:
            print(arr);
            break;
        case 3:
            printf("Enter key value to search: ");
            scanf("%d", &keyVal);
            int result = search(arr, keyVal);
            if (result != -1) {
                printf("Key %d found at index %d\n", keyVal, result);
            } else {
                printf("Key %d not found\n", keyVal);
            }
            break;
        case 4:
            printf("Enter key value to delete: ");
            scanf("%d", &keyVal);
            deleteKey(arr, keyVal);
            break;
        case 5:
            flag=false;
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    
}