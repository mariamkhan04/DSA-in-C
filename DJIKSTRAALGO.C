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

// Function to perform Dijkstra's algorithm
void dijkstra(struct Vertex* sourceVertex) {
    sourceVertex->distance = 0; //This line initializes the distance of the sourceVertex to 0. In Dijkstra's algorithm, the distance of the source vertex to itself is always 0, and the distances to other vertices are initialized to infinity.
    struct Vertex* current = sourceVertex;

    while (current != NULL) { //The loop will continue until all vertices have been visited.
        struct Edge* ecurr = current->Elist;
        while (ecurr != NULL) {
            struct Vertex* neighbor = ecurr->toVertex;//It represents the neighboring vertex to the current vertex.
            int distance = current->distance + ecurr->weight;

            if (distance < neighbor->distance) {
                neighbor->distance = distance;
                neighbor->previous = current; //The previous pointer of the neighbor vertex is updated to point to the current vertex. This is done to keep track of the path that led to the neighbor in the shortest path.
            }
            ecurr = ecurr->enext;
        }

        current->visited = true; //After processing all neighbors, the current vertex is marked as visited, meaning that the shortest path to it has been determined.
        current = NULL; //current ko NULL par set kiya jata hai taki ham dobara se sabhi vertices ke distances ko compare kar sake. TO FIND NEXT VERTEX
        int minDistance = INT_MAX;

        struct Vertex* vcurr = graph;
        //Yeh loop har vertex ke distances ko compare karne ke liye iterate karta hai
        while (vcurr != NULL) {
            if (!vcurr->visited && vcurr->distance < minDistance) {
                current = vcurr;
                minDistance = vcurr->distance;
            }
            vcurr = vcurr->vnext;
        }
    }
}

// Function to print the shortest path from the source to a destination vertex
void printShortestPath(struct Vertex* destinationVertex) {
    if (destinationVertex->previous != NULL) {
        printShortestPath(destinationVertex->previous);
        printf(" -> ");
    }
    printf("%c", destinationVertex->name);
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
            dijkstra(sourceVertex); //This calculates the shortest paths and updates the distance and previous fields for all vertices.
            printf("Shortest Paths from %c:\n", source);
            struct Vertex* vcurr = graph;
            while (vcurr != NULL) {
                if (vcurr->distance == INT_MAX) { //Checks if the distance field of the current vertex vcurr is still set to its initial value of INT_MAX, which indicates that no path exists from the source vertex to this vertex.
                    printf("%c -> %c: No path\n", source, vcurr->name);
                } else {
                    printf("%c -> %c: %d (Path: %c ", source, vcurr->name, vcurr->distance, source);
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
