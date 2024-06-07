#include<stdio.h>
#include<stdlib.h>
void binarySearch(int arr[],int size,int left,int right,int toSearch){
    int mid;
    int found=0;
    while(left<=right)
    {
        mid=(left+right)/2;
        if (toSearch==arr[mid])
        {
            printf("element %d found at index %d\n",toSearch,mid);
            found++;
            break;
        }else if(toSearch<arr[mid]){
            right=mid-1;
        }else{
            left=mid+1;
        }
    }
if (found==0)
{
    printf("Element not found\n");
}
}
void printArr(int arr[],int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d\t",arr[i]);
    }
}
int main(){
    int arr[10],size,toSearch;
    printf("Enter the size of arr: ");
    scanf("%d",&size);
    for (int i = 0; i < size; i++)
    {
        printf("enter elements: ");
        scanf("%d",&arr[i]);
    }
    printf("Enter the element that you want to search: ");
    scanf("%d",&toSearch);
    binarySearch(arr,size,0,size-1,toSearch);
    printArr(arr,size);
    return 0;
}