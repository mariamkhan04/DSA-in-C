// program to dynamically allocate memory for struct and access trough ptr
#include<stdio.h>
#include<stdlib.h>

struct Student {
  int id;
  int marks;
};

int main() {
  // for input
  for (int i = 0; i < 3; i++) {
    struct Student *stdptr = (struct Student *)malloc(sizeof(struct Student));

    printf("enter Studnet %d info: \n", i + 1);
    printf("Enter id: ");
    scanf("%d", &stdptr->id);
    printf("Enter Marks: ");
    scanf("%d", &stdptr->marks);

    // for output
    printf("Student %d info is: \n", i + 1);
    printf("Id is %d\n", stdptr->id);
    printf("Marks are %d\n", stdptr->marks);

    // free the dynamically allocated memory
    free(stdptr);
  }

  return 0;
}