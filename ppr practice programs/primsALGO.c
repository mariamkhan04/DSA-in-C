#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
struct vertex{
    char data;
    bool visited;
    struct vertex *vnext;
    struct edge *estart;
} *graphst=NULL;
struct edge{
    int weight;
    struct vertex *tovertex;
    struct edge *enext;
};
void insertVertex(char data){
    struct vertex *temp=(struct vertex *)malloc(sizeof(struct vertex));
    temp->data=data;
    temp->visited=false;
    temp->vnext=NULL;
    temp->estart=NULL;
    if(graphst==NULL){
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
void insertEdges(char s,char d,int weight){
    struct vertex *vcurr=graphst;
    struct vertex *source=NULL; //to track source vertex in graph
    struct vertex *dest=NULL; //to track destination vertex in graph

    while (vcurr!=NULL)
    {
        if (vcurr->data==s){
            source=vcurr;
        }else if (vcurr->data==d){
            dest=vcurr;
        }
        vcurr=vcurr->vnext;
    } //after this loop we have successfully find source and dest vertex
    if(source!=NULL&&dest!=NULL){   //agr null huay means humme source and dest nhi mili and we cant insert the edge
        struct edge *temp=(struct edge *)malloc(sizeof(struct edge));
        temp->weight=weight;
        temp->tovertex=dest;
        temp->enext=NULL;
        if(source->estart==NULL){
            source->estart=temp;
        }else{
            struct edge *ecurr=source->estart;
            while (ecurr->enext!=NULL)
            {
                ecurr=ecurr->enext;
            }
            ecurr->enext=temp;
        }

        //adding reverse edges as it is undirected graph
        temp=(struct edge *)malloc(sizeof(struct edge));
        temp->weight=weight;
        temp->tovertex=source;
        temp->enext=NULL;
        if(dest->estart==NULL){
            dest->estart=temp;
        }else{
            struct edge *ecurr=dest->estart;
            while (ecurr->enext!=NULL)
            {
                ecurr=ecurr->enext;
            }
            ecurr->enext=temp;
        }
    }
}
void dfs(struct vertex *v){
    if(v==NULL){
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
        return false;
    }
    dfs(graphst);
    struct vertex *vcurr=graphst;
    while (vcurr!=NULL)
    {
        if(!vcurr->visited){
            return false;
        }
        vcurr=vcurr->vnext;
    }
    return true;
}
//prim's algorithm
int primMST(){
    if (graphst==NULL)
    {
        printf("graph is empty\n");
        return 0;
    }
    char included[128];
    int key[128];
    char parent[128];

    for (int i = 0; i < 128; i++)
    {
        included[i]=false;
        key[i]=INT_MAX;
        parent[i]=-1;
    }
    key[graphst->data]=0;
    int totalCost=0;
    for (struct vertex *u = graphst; u!=NULL; u=u->vnext)
    {
        char minvertex=0;
        int minkey=INT_MAX;
        for (struct vertex *v = graphst; v!=NULL; v=v->vnext)
        {
            if(!included[v->data]&&key[v->data]<minkey){
                minvertex=v->data;
                minkey=key[v->data];
            }
        }
        included[minvertex]=true;
        struct vertex *uVertex=NULL; //minVertex ke corresponding vertex ko graph mai point karega
        for (struct vertex *v=graphst ; v!=NULL; v=v->vnext)
        {
            if (v->data==minvertex)
            {
                uVertex=v;
                break;
            }
        }
        //uVertex se originate hone wali sab edges ko check karenge taake unke parent and key value ko mark kr saken (taake humme aage min weight wali edge dhoondne mai mushkil na ho)
        for (struct edge *e=uVertex->estart;e!=NULL;e=e->enext)
        {
            if (!included[e->tovertex->data]&&e->weight<key[e->tovertex->data])
            {
                parent[e->tovertex->data]=uVertex->data;
                key[e->tovertex->data]=e->weight;
            }
        }
    }
    //printing mst
    printf("Minimum Spanning Tree: \n");
    for (char i = 'A'; i <= 'Z'; i++)
    {
        if (parent[i]!=-1)
        {
            printf("Edge: %c - %c, Weight: %d\n",parent[i],i,key[i]);
            totalCost=totalCost+key[i];
        }
    }
    return totalCost;
}
int main(){
    int numVertices,numEdges;
    printf("Enter number of vertices: ");
    scanf("%d",&numVertices);
    for (int i = 0; i < numVertices; i++)
    {
        char data;
        printf("Enter the vertex label(A,B,C,etc): ");
        scanf(" %c",&data);
        insertVertex(data);
    }
    printf("Enter the number of edges: ");
    scanf("%d",&numEdges);
    for (int i = 0; i < numEdges; i++)
    {
        int weight;
        char source,destination;
        printf("Enter source vertex: ");
        scanf(" %c",&source);
        printf("Enter destination vertex: ");
        scanf(" %c",&destination);
        printf("Enter weight: ");
        scanf("%d",&weight);
        insertEdges(source,destination,weight);
    }
    if(isConnected()){
        int minCost=primMST();
        printf("Minimum cost of mst: %d\n",minCost);
    }else{
        printf("The graph is not connected");
    }
    return 0;
}