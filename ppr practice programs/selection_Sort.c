#include<stdio.h>
#include<stdlib.h>
void swap(int *min,int *j){
    int temp=*min;
    *min=*j;
    *j=temp;
}
int SelectionSort(int arr[],int size){
    int totalSwaps=0,min;
    for (int i = 0; i < size-1; i++)
    {
        min=arr[i];
        for (int j = i+1; j < size; j++)
        {
            if(arr[j]<min){
                swap(&min,&arr[j]);
                totalSwaps++;
            }
        }
        arr[i]=min;
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
    totalswaps=SelectionSort(arr,size);
    printf("array after sorting\n");
    printArr(arr,size);
    printf("Total no of swaps to sort the array:%d ",totalswaps);
    return 0;
}