#include<stdio.h>
#include<stdlib.h>

int binary_search(int arr[],int elem,int left,int right){
    int bool=0;
    while(left<=right){
        int mid = (left+right)/2;
        if(elem==arr[mid]){
            return mid;
        }
        else if(elem>arr[mid]){
            left=mid+1;
        }else{
            right=mid-1;
        }
    }
    if(bool==0){
        return -1;
    }
}
int main(){
    int arr[]={22,28,32,39,56,57,80,82,86,88};
    int elem=28;
    int size=sizeof(arr)/sizeof(arr[0]);
    int result = binary_search(arr,elem,0,size-1);
    if(result==-1){
        printf("element not found");
    }
    else{
        printf("element found at index %d",result);
    }
}