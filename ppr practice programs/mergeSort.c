#include<stdio.h>
#include<stdlib.h>
void mergeSort(int arr[],int left,int right){
    if(left<right){
        int mid=(left+right)/2;
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}