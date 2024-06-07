#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

struct vertex
{
    char data;
    bool visited;
    struct vertex *vnext;
    struct edge *estart;
} *graphst=NULL;

struct edge
{
    int weight;
    struct vertex *tovertex;
    struct edge *enext;
};

struct KruskalEdge
{
    char source;
    char destination;
    int weight;
};

void insertVertex(char data){
    struct vertex *temp=(struct vertex *)malloc(sizeof(struct vertex));
    temp->data=data;
    temp->visited=false;
    temp->estart=NULL;
    temp->vnext=NULL;
    if (graphst==NULL)
    {
        graphst=temp;
    }else{
        struct vertex *vcurr=graphst;
        while (vcurr->vnext!=NULL)
        {
            vcurr=vcurr->vnext;
        }
        vcurr->vnext=temp;
    }
}
void insertEdge(char source,char destination,int weight){
    struct vertex *vcurr=graphst;
    struct vertex *sourceVertex=NULL;
    struct vertex *destVertex=NULL;

    while (vcurr!=NULL)
    {
        if (vcurr->data==source)
        {
            sourceVertex=vcurr;
        }else if(vcurr->data==destination){
            destVertex=vcurr;
        }
        vcurr=vcurr->vnext;
    }
    if (sourceVertex!=NULL && destVertex!=NULL)
    {
        struct edge *temp= (struct edge *)malloc(sizeof(struct edge));
        temp->tovertex=destVertex;
        temp->weight=weight;
        temp->enext=NULL;
        if (sourceVertex->estart==NULL)
        {
            sourceVertex->estart=temp;
        }else{
            struct edge *ecurr=sourceVertex->estart;
            while (ecurr->enext!=NULL)
            {
                ecurr=ecurr->enext;
            }
            ecurr->enext=temp;
        }

        //adding reverse edge
        temp=(struct edge *)malloc(sizeof(struct edge));
        temp->tovertex=sourceVertex;
        temp->weight=weight;
        temp->enext=NULL;
        if (destVertex->estart==NULL)
        {
            destVertex->estart=temp;
        }else{
            struct edge *ecurr=destVertex->estart;
            while (ecurr->enext!=NULL)
            {
                ecurr=ecurr->enext;
            }
            ecurr->enext=temp;
        }
    }   
}
void dfs(struct vertex *v){
    if (v==NULL)
    {
        return;
    }
    v->visited=true;
    struct edge *ecurr=v->estart;
    while (ecurr!=NULL)
    {
        if(!ecurr->tovertex->visited){
            dfs(ecurr->tovertex);
        }
        ecurr=ecurr->enext;
    }
}
bool isConnected(){
    if(graphst==NULL){
        printf("Graph is empty\n");
        return false;
    }
    dfs(graphst);
    struct vertex *vcurr=graphst;
    while (vcurr!=NULL)
    {
        if (!vcurr->visited)
        {
            return false;
        }
        vcurr=vcurr->vnext;
    }
    return true;
}
int compareEdges(const void *a,const void *b){
    return ((struct KruskalEdge*)a)->weight-((struct KruskalEdge *)b)->weight;
}
bool isSameComponent(char v1,char v2,int *component){
    return component[v1]==component[v2];
}
void unionComponents(char v1,char v2,int *component){
    int compV1=component[v1];
    int compV2=component[v2];
    for (int i = 0; i <= 128; i++)
    {
        if (component[i]==compV2)
        {
            component[i]=compV1;
        }
    }
}
void kruskalMST(){
    int totalMSTCost=0;
    if (!isConnected())
    {
        printf("Graph is not connect, mst can not be found\n");
        return;
    }
    struct KruskalEdge edges[1000]; //arr to store all edges
    int edgeCount=0;
    struct vertex *v=graphst;
    //traverse the graph and add all edges to edges arr
    while (v!=NULL)
    {
        struct edge *e=v->estart;
        while (e!=NULL)
        {
            if (v->data < e->tovertex->data) //taake duplicate edges add naa hoon
            {
                edges[edgeCount].source=v->data;
                edges[edgeCount].destination=e->tovertex->data;
                edges[edgeCount].weight=e->weight;
                edgeCount++;
            }
            e=e->enext;
        }
        v=v->vnext;
    }
    //sort all edges in edges arr in ascending order  of weight using qsort which uses compareEdges function to sort
    qsort(edges,edgeCount,sizeof(struct KruskalEdge),compareEdges);
    //sizeof(struct kruskalEdge) array mai har element ka size
    //compareEdges function to compare two edges(jiska weight kam hua it will come first in sorted arr)
    int component[128]; //component array me har vertex ke liye ek alag component number initialize hota hai
    for (int i = 0; i < 128; i++)
    {
        component[i]=i; 
    }
    printf("Minimum Spanning tree: \n");
    //iss loop mai sorted edges one by one check hoti hain jiske add krne se cycle nhi banta usse mst mai add krte hain or union func se unn vertices ko one component mai krdete hain
    for (int i = 0; i < edgeCount; i++)
    {
        char source=edges[i].source;
        char dest=edges[i].destination;
        int weight=edges[i].weight;

        if(!isSameComponent(source,dest,component)){
            printf("%c - %c: %d\n",source,dest,weight);
            unionComponents(source,dest,component);
            totalMSTCost+=weight;
        }
    }
    printf("Total cost of mst: %d\n",totalMSTCost);
}
// Function to free the allocated memory for the graph
void freeGraph() {
    struct vertex* v = graphst;
    while (v != NULL) {
        struct edge* e = v->estart;
        while (e != NULL) {
            struct edge* temp = e;
            e = e->enext;
            free(temp);
        }
        struct vertex* temp = v;
        v = v->vnext;
        free(temp);
    }
}
int main(){
    int choice,weight;
    char source, destination, data;
    while (1)
    {
        printf("MENU\n1. insert a vertex\n2. Insert an edge\n3. display MST\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("Enter the vertex data: ");
            scanf(" %c", &data);
            insertVertex(data);
            break;
        case 2:
            printf("Enter source: ");
            scanf(" %c", &source);
            printf("Enter destination vertex: ");
            scanf(" %c", &destination);
            printf("Enter edge weight: ");
            scanf("%d", &weight);
            insertEdge(source, destination, weight);
            break;
        case 3:
            kruskalMST();
            break;
        case 4:
            freeGraph();
            exit(0);
        default:
            printf("Enter valid choice please!");
            break;
        }
    }   
    return 0;
}