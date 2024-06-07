#include<stdio.h>
#include<stdlib.h>
int insertionSort(int arr[],int size){
    int count=0;
    for(int i=0;i<size;i++){
        int hold = arr[i];
        int j= i-1;
        while(hold < arr[j] && j>=0){
            arr[j+1]=arr[j];
            --j;
            count++;
        } 
        arr[j+1]=hold;
    }
    printf("Total swaps to sort the array are %d\n",count);
}
int main(){
    int arr[]={20,89,90,30,11,56,28,77};
    int size= sizeof(arr)/sizeof(arr[0]);
    insertionSort(arr,size);
    printf("\tSorted Array in ascending order:\n");
    for(int i=0;i<size;i++){
        printf("%d\t",arr[i]);
    }
}