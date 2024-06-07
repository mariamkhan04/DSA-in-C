#include<stdio.h>
#include<stdlib.h>
int insertionSort(int arr[],int size){
    int totalSwaps=0;
    for (int i = 0; i < size; i++)
    {
        int hold=arr[i];
        int j=i-1;
        while (arr[j]>hold&&j>=0)
        {
            arr[j+1]=arr[j];
            totalSwaps++;
            j--;
        }
        arr[j+1]=hold;
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
    totalswaps=insertionSort(arr,size);
    printf("array after sorting\n");
    printArr(arr,size);
    printf("Total no of swaps to sort the array:%d ",totalswaps);
    return 0;
}