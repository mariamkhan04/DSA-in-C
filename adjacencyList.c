/* Adjacency list for directed graph with all operations*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct vertex{
    char data;
    struct vertex *next;
    struct edge *elist;
} *graphst=NULL;

struct edge{
    struct vertex *tovertex;
    struct edge *next;
} *elist = NULL;
//function to add a vertex
void insertVertices(){
    struct vertex *temp = (struct vertex *)malloc(sizeof(struct vertex));
    printf("Enter vertex: ");
    scanf(" %c",&temp->data);
    temp->next = NULL;
    temp->elist =NULL;
    if(graphst == NULL){
        graphst = temp;
    }else{
        struct vertex *vcurr = graphst;
        while(vcurr->next != NULL){
            vcurr = vcurr->next;
        }
        vcurr->next=temp;
    }
}
//function to add an edge
void insertEdge(){
    char source;
    printf("Enter source: ");
    scanf(" %c",&source);
    struct vertex *vcurr = graphst;
    while(vcurr != NULL){
        if(source == vcurr->data){
            struct edge *temp = (struct edge *)malloc(sizeof(struct edge));
            printf("Enter destination: ");
            scanf(" %c",&temp->tovertex);
            temp->next=NULL;
            if(vcurr->elist == NULL){
                vcurr->elist=temp;
            }else{
                struct edge *ecurr = vcurr->elist;
                while(ecurr->next!=NULL){
                    ecurr=ecurr->next;
                }
                ecurr->next =temp;
            }
            return;
        }
        vcurr=vcurr->next;
    }
    printf("Vertex not found\n");
}
//function to print out-degree
int printOutDegree(){
    char source;
    int outDegree=0;
    printf("Enter source: ");
    scanf(" %c",&source);
    struct vertex *vcurr = graphst;
    while(vcurr!=NULL){
        if(vcurr->data == source){
            break;
        }
        vcurr=vcurr->next;
    }
    if(vcurr == NULL){
        printf("invalid vertex\n");
        return -1;
    }
    struct edge *ecurr = vcurr->elist;
    if(ecurr == NULL){
        printf("no edges\n");
    }else{
        while(ecurr != NULL){
            outDegree++;
            ecurr=ecurr->next;
        }
    }
    printf("Out Degree is %d\n", outDegree);
    return outDegree;
}
//function to print in-degree
int printInDegree(){
    int inDegree=0;
    char vertex;
    printf("Enter vertex: ");
    scanf(" %c",&vertex);
    struct vertex *vcurr = graphst;
    while(vcurr!=NULL){
        struct edge *ecurr = vcurr->elist;
            while(ecurr!=NULL){
                if(ecurr->tovertex->data==vertex){
                    inDegree++;
                }
                ecurr=ecurr->next;
            }
        vcurr = vcurr->next;
    }
    printf("In Degree is %d\n", inDegree);
}
void printVertices(){
    struct vertex *vcurr = graphst;
     while(vcurr!=NULL){
         printf("Vertices are: %c\t", vcurr->data);
         vcurr=vcurr->next;
     }
}
void printVerticesAndEdges(){
    struct vertex *vcurr = graphst;
    while(vcurr!=NULL){
        printf("vertex %c:  ",vcurr->data);
        struct edge *ecurr = vcurr->elist;
            if(ecurr==NULL){
                printf("no edge\n");
            }
            while(ecurr!=NULL){
                printf("%c\t",ecurr->tovertex);
                ecurr = ecurr->next;
            }
        printf("\n");
        vcurr = vcurr->next;
    }
}
int main(){
    int choice,lengthList;
    bool flag = true;
    while(flag==true){
        printf("Options\n1. Insert Vertex\n2. Insert Edge\n3. Print Out-degree\n4. Print In-Degree\n5. PrintAll\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter length of list: ");
                scanf("%d",&lengthList);
                for(int i=0;i<lengthList;i++){
                    insertVertices();
                }
            break;
            case 2:
                insertEdge();
            break;
            case 3:
                printOutDegree();
            break;
            case 4:
                printInDegree();
            break;
            case 5:
                printVerticesAndEdges();
            break;
            case 6:
                flag=false;
            break;
            default:
            printf("Invalid choce\n");
        }
    }
    return 0;
}

