#include<stdio.h>
#include<stdlib.h>
void swap(int *x,int *y){
    int temp= *x;
    *x=*y;
    *y=temp;
}
int BubbleSort(int arr[],int size){
    int totalSwaps=0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size-i-1; j++)
        {
            if (arr[j]>arr[j+1])
            {
                swap(&arr[j],&arr[j+1]);
                totalSwaps++;
            }
        }
    }
    return totalSwaps;
}
void printArr(int arr[],int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d\t",arr[i]);
    }
    printf("\n");
}
int main(){
    int arr[10],size,totalswaps;
    printf("Enter size: ");
    scanf("%d",&size);
    for (int i = 0; i < size; i++)
    {
        printf("Enter elements: ");
        scanf("%d",&arr[i]);
    }
    printf("array before sorting\n");
    printArr(arr,size);
    totalswaps=BubbleSort(arr,size);
    printf("array after sorting\n");
    printArr(arr,size);
    printf("Total no of swaps to sort the array:%d ",totalswaps);
    return 0;
}