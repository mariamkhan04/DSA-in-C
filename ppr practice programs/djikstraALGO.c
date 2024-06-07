#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Structure for a vertex
struct Vertex {
    char name;
    int distance;
    bool visited;
    struct Edge* Elist;
    struct Vertex* previous;
    struct Vertex* vnext;
};

// Structure for an edge
struct Edge {
    struct Vertex* toVertex;
    int weight;
    struct Edge* enext;
};

// Global variable to keep track of the graph's vertices
struct Vertex* graph = NULL;

// Function to add a vertex to the graph
void insertVertex(char data) {
    struct Vertex* temp = (struct Vertex*)malloc(sizeof(struct Vertex));
    temp->name = data;
    temp->distance = INT_MAX;
    temp->visited = false;
    temp->Elist = NULL;
    temp->previous = NULL;
    temp->vnext = NULL;

    if (graph == NULL) {
        graph = temp;
    } else {
        struct Vertex* vcurr = graph;
        while (vcurr->vnext != NULL) {
            vcurr = vcurr->vnext;
        }
        vcurr->vnext = temp;
    }
}

// Function to add an edge with weight to the graph
void insertEdge(char source, char destination, int weight) {
    struct Vertex* vcurr = graph;
    struct Vertex* sourceVertex = NULL;
    struct Vertex* destVertex = NULL;

    while (vcurr != NULL) {
        if (vcurr->name == source) {
            sourceVertex = vcurr;
        } else if (vcurr->name == destination) {
            destVertex = vcurr;
        }
        vcurr = vcurr->vnext;
    }

    if (sourceVertex != NULL && destVertex != NULL) {
        struct Edge* temp = (struct Edge*)malloc(sizeof(struct Edge));
        temp->toVertex = destVertex;
        temp->weight = weight;
        temp->enext = NULL;

        if (sourceVertex->Elist == NULL) {
            sourceVertex->Elist = temp;
        } else {
            struct Edge* ecurr = sourceVertex->Elist;
            while (ecurr->enext != NULL) {
                ecurr = ecurr->enext;
            }
            ecurr->enext = temp;
        }

        // Adding the reverse edge as well since it's an undirected graph
        temp = (struct Edge*)malloc(sizeof(struct Edge));
        temp->toVertex = sourceVertex;
        temp->weight = weight;
        temp->enext = NULL;

        if (destVertex->Elist == NULL) {
            destVertex->Elist = temp;
        } else {
            struct Edge* ecurr = destVertex->Elist;
            while (ecurr->enext != NULL) {
                ecurr = ecurr->enext;
            }
            ecurr->enext = temp;
        }
    }
}
void djikstra(struct Vertex *sourceVertex){
    sourceVertex->distance=0;
    struct Vertex *vcurr=sourceVertex;
    while (vcurr!=NULL) //loop will continue until all vertices are visited and minimumdistance are found
    {
        struct Edge *ecurr=vcurr->Elist;
        //to check all neighbours and set their parents and distances
        while (ecurr!=NULL)
        {
            struct Vertex *neighbour=ecurr->toVertex;
            int distance=vcurr->distance+ecurr->weight;
            if(distance<neighbour->distance){
                neighbour->distance=distance;
                neighbour->previous=vcurr;
            }
            ecurr=ecurr->enext;
        }
        vcurr->visited=true;
        //TO FIND NEXT VERTEX with minimum distance
        vcurr=NULL;
        int minDistance=INT_MAX;
        struct Vertex *curr=graph;
        while (curr!=NULL)
        {
            if (!curr->visited && curr->distance<minDistance)
            {
                vcurr=curr;
                minDistance=curr->distance;
            }
            curr=curr->vnext;
        }
    }
}
void printShortestPath(struct Vertex *destVertex){
    if(destVertex->previous!=NULL){
        printShortestPath(destVertex->previous);
        printf(" -> ");
    }
    printf("%c", destVertex->name);
}
int main() {
    // Example usage of the program
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    for (int i = 0; i < numVertices; i++) {
        char vertexData;
        printf("Enter the vertex label (A, B, C, etc.): ");
        scanf(" %c", &vertexData);
        insertVertex(vertexData);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        char source, destination;
        int weight;
        printf("Enter source vertex: ");
        scanf(" %c", &source);
        printf("Enter destination vertex: ");
        scanf(" %c", &destination);
        printf("Enter edge weight: ");
        scanf("%d", &weight);
        insertEdge(source, destination, weight);
    }

    char source;
    printf("Enter Source Vertex: ");
    scanf(" %c", &source);
    struct Vertex* sourceVertex = graph;
    while (sourceVertex != NULL) {
        if (source == sourceVertex->name) {
            djikstra(sourceVertex); //This calculates the shortest paths and updates the distance and previous fields for all vertices.
            printf("Shortest Paths from %c:\n", source);
            struct Vertex* vcurr = graph;
            while (vcurr != NULL) {
                if (vcurr->distance == INT_MAX) { //Checks if the distance field of the current vertex vcurr is still set to its initial value of INT_MAX, which indicates that no path exists from the source vertex to this vertex.
                    printf("%c -> %c: No path\n", source, vcurr->name);
                } else {
                    printf("%c -> %c: %d (Path: %c", source, vcurr->name, vcurr->distance, source);
                    printShortestPath(vcurr);
                    printf(")\n");
                }
                vcurr = vcurr->vnext;
            }
            break;
        }
        sourceVertex = sourceVertex->vnext;
    }

    return 0;
}