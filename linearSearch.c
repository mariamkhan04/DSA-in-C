// Linear search program to find all occurences of element
#include<stdio.h>
#include<stdlib.h>

int Linear_search(int arr[],int size,int to_search){
    int bool=0;
    int count=0;
    for(int i=0; i<size; i++){
        if(to_search==arr[i]){
            printf("element found at index %d\n",i);
            bool=1;
            count+=1;
            // break;
        }
    }
    if(bool==0){
        printf("element not found");
        return -1;
    }
    printf("element occured %d times",count);
}
int main(){
    int arr[]={32,55,78,49,55,32};
    int size=sizeof(arr)/sizeof(arr[0]);
    int to_search = 32;
    Linear_search(arr,size,to_search);
}