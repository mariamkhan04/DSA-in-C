//access array elements using pointers
#include<stdio.h>
#include<stdlib.h>
int print_Array(int arr[],int size){
    int *ptr= arr; // pointer variable ptr of type int *, which means it can store the memory address of an integer. The pointer is initialized to point to the first element of the arr array. Since the array name arr itself represents the memory address of the first element, we don't need to use the address-of operator &.
    for(int i=0;i<size;i++){
        printf("%d\t",*ptr); //*ptr is used to dereference the pointer and get the value it points to.
        ptr++;
    }
}
int main(){
    int arr[]={6,3,2,9,1};
    int size=5;
    print_Array(arr,size);
}