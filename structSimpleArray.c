// program simple struct,array,input and output
#include<stdio.h>
#include<stdlib.h>
struct Student{
    int id;
    int marks;
    float gpa;
};
int main(){
    int size=3;
    struct Student arr[3];

    //input array
    for(int i=0;i<size;i++){
        printf("ID: ");
        scanf("%d", &arr[i].id);

        printf("Marks: ");
        scanf("%d", &arr[i].marks);

        printf("GPA: ");
        scanf("%f", &arr[i].gpa);
    }
    for (int i = 0; i < size; i++)
    {
        printf("Id: %d\n",arr[i].id);
        printf("Marks: %d\n",arr[i].marks);
        printf("GPA: %f\n",arr[i].gpa);
    }
    
    return 0;
}