#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Course{
    int courseNo;
    struct Course *next;
    struct Student *sstart;
} *cstart = NULL;

struct Student{
    int studentId;
    struct Student *next;
} *sstart = NULL;

// to insert course 
void insertCourse(){
    struct Course *temp= (struct Course *)malloc(sizeof(struct Course));
    printf("Enter course # : ");
    scanf("%d",&temp->courseNo);
    temp->next = NULL;
    temp->sstart = NULL;

     if(cstart == NULL){
        cstart = temp;
     }
     else{
        struct Course *curr = cstart;
        while(curr->next != NULL){
            curr =curr->next;
        }
        curr->next=temp;
     }
}

// to insert students in courses
void insertStudent(){
    // allocates memory for new student node 
    struct Student *temp = (struct Student *)malloc(sizeof(struct Student));
    printf("Enter Student ID: ");
    scanf("%d",&temp->studentId);
    temp->next = NULL; //sets the next pointer of new student node to NULL

    int cNo;
    printf("Enter Course NO: ");
    scanf("%d",&cNo);
    struct Course *ccurr = cstart;
    while(ccurr != NULL){
        //check if the current course node has entered course number
        if(ccurr->courseNo == cNo){
            struct Student *sstart = ccurr->sstart;
            // if course exists, then check if linked list of students is empty 
            if(sstart == NULL){
                //if yes, sstart pointer of current course is set to new student node(ie, temp) 
                ccurr->sstart = temp;
            } 
            // otherwise ,  the function traverses the linked list of students for that course and inserts the new student node when scurr->next equal to NULL
            else{
                struct Student *scurr= sstart;
                while(scurr->next != NULL){
                    scurr = scurr->next;
                }
                scurr->next = temp;
            }
            ccurr = ccurr->next;
            break;
        }
        ccurr=ccurr->next; //moves to next course node
    }
    if(ccurr==NULL){
        printf("Course not found\n");
    }
}

void printStduents(){
    int cNo;
    printf("Enter course: ");
    scanf("%d",&cNo);
    struct Course *ccurr = cstart;
    while(ccurr != NULL){
        if(ccurr->courseNo == cNo){
            struct Student *scurr = sstart;
            printf("students in course %d are: ",cNo);
            while(scurr != NULL){
                printf("Students Ids are: %d\n",scurr->studentId);
                scurr = scurr->next;
            }
            printf("\n");
            return;
        }
        ccurr = ccurr->next;
    }
}

void printCourses(){
    struct Course *ccurr = cstart;
    while(ccurr != NULL){
        printf("Courses are: %d\n",ccurr->courseNo);
        // printStduents(ccurr->sstart);
        ccurr = ccurr->next;
    }
}
int main(){
    int choice,LengthList;
    bool flag= true;
    while(flag == true){
        printf("\tOptions\t\n");
        printf("1. InsertCourse\n");
        printf("2. InsertStudent\n");
        printf("3. PrintCourses\n");
        printf("4. PrintStudents\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Enter Course list size: "); 
                scanf("%d",&LengthList);
                for (int i = 0; i < LengthList; i++)
                {
                    insertCourse();    
                }
            break;
            case 2:
                printf("Enter Student list size: "); 
                scanf("%d",&LengthList);
                for (int i = 0; i < LengthList; i++)
                {
                    insertStudent();    
                }
            break;
            case 3:
                printCourses();
            break;
            case 4:
                printStduents();
            break;
            case 5:
                printf("Program Finished\n");
                flag = false;
            break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}