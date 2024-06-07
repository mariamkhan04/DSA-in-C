#include <stdio.h>
#include<stdlib.h>
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to build a max heap
void buildMaxHeap(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int child = i;
        while (child > 0) {
            int parent = (child - 1) / 2;
            if (arr[child] > arr[parent]) {
                swap(&arr[child], &arr[parent]);
                child = parent;
            } else {
                break;
            }
        }
    }
}
void maxHeapSort(int arr[],int size){
    for (int i = size-1; i >=0; i--)
    {
        swap(&arr[0],&arr[i]);
        int parent=0;
        int child=1;
        while (child<i)
        {
            //greatest chils select karenge
            if(child+1<i && arr[child]<arr[child+1]){
                child++;
            }
            //child and parent ki value ko dekhenge agr parent ki value small hui child se tou swapping hogi or child parent ban jayega phr uska child dhoondenge
            if(arr[parent]<arr[child]){
                swap(&arr[parent],&arr[child]);
                parent=child;
                child=2*parent+1;
            }else{
                break;
            }
        }
    }
}
int main(){
    int *arr=NULL;
    int size=0;
    int value;
    printf("Enter the value you want to insert and press -1 for stop: ");
    while(1){
        scanf("%d",&value);
        if (value==-1)
        {
            break;
        }
        size++;
        arr=(int *)realloc(arr,size*sizeof(int));
        arr[size-1]=value;
    }
    printf("Input array: ");
    for (int i = 0; i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    buildMaxHeap(arr,size);
    printf("Max heap array: ");
    for (int i = 0; i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    // Sort the max-heap
    maxHeapSort(arr,size);
    printf("Sorted Max heap array: ");
    for (int i = 0; i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}