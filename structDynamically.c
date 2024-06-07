// program to dynamically allocate memory for struct and access trough ptr
#include<stdio.h>
#include<stdlib.h>
struct Student{
    int id;
    int marks;
};
int main(){
    struct Student *stdptr=(struct Student *)malloc(sizeof(struct Student));
    stdptr->id=24;
    stdptr->marks=88;
    printf("Id is %d\n",stdptr->id);
    printf("Marks are %d\n",stdptr->marks);
    return 0;
}