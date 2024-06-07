#include<stdio.h>
#include<stdlib.h>

int binarySearch(int arr[],int elem,int left,int right){
    if (left> right){
        return -1;
    } 
    else{
        int mid = (left + right) / 2;
        if (elem == arr[mid]){
            return mid;
        }
        else if (elem > arr[mid]){        // x is on the right side
            return binarySearch(arr, elem, mid + 1, right);
        }
        else{                           // x is on the left side
            return binarySearch(arr, elem, left, mid - 1);
        }
    }
}
int main(){
    int arr[]={22,28,32,39,56,57,80,82,86,88};
    int elem=82;
    int size=sizeof(arr)/sizeof(arr[0]);
    int result = binarySearch(arr,elem,0,size-1);
    if(result==-1){
        printf("element not found");
    }
    else{
        printf("element found at index %d",result);
    }
}