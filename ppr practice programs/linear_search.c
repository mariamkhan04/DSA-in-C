#include<stdio.h>
#include<stdlib.h>
void linearSearch(int arr[],int size,int toSearch){
    int found=0;
    for(int i=0;i<size;i++){
        if(toSearch==arr[i]){
            printf("Element %d is found on index %d\n",toSearch,i);
            found++;
        }
    }
if (found==0)
{
    printf("Element not found");
}
}
void printArray(int arr[],int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d\t",arr[i]);
    }
    printf("\n");
}
int main(){
    int arr[10],size,toSearch;
    printf("Enter the size of array: ");
    scanf("%d",&size);
    for (int i = 0; i < size; i++)
    {
        printf("Enter elements: ");
        scanf("%d",&arr[i]);
    }
    printf("Enter the elemnet that you want to search: ");
    scanf("%d",&toSearch);
    linearSearch(arr,size,toSearch);
    printArray(arr,size);
    return 0;
}