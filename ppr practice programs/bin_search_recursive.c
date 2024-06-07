#include<stdio.h>
#include<stdlib.h>
int binSearch(int arr[],int size,int left,int right,int toSearch){
    int mid;
    while (left<=right)
    {
        mid=(left+right)/2;
        if(toSearch==arr[mid]){
            return mid;
        }else if(toSearch<arr[mid]){
            return binSearch(arr,size,left,mid-1,toSearch);
        }else{
            return binSearch(arr,size,mid+1,right,toSearch);
        }
    }
    return -1;
}
void printArr(int arr[],int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d\t",arr[i]);
    }
}
int main(){
    int arr[10],size,toSearch;
    printf("Enter the size: ");
    scanf("%d",&size);
    for (int i = 0; i < size; i++)
    {
        printf("Enter element: ");
        scanf("%d",&arr[i]);
    }
    printf("Enter the element you want to search: ");
    scanf("%d",&toSearch);
    int result=binSearch(arr,size,0,size-1,toSearch);
    if (result==-1)
    {
        printf("Element not found\n");
    }else{
        printf("Element %d found at index %d\n",toSearch,result);
        printArr(arr,size);
    }
    return 0;
}