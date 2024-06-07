#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Structure for a vertex
struct vertex {
    char data;
    struct vertex* vnext;
    struct edge* estart;
} *graphst = NULL;

// Structure for an edge
struct edge {
    struct vertex* tovertex;
    int weight;
    struct edge* enext;
};

// Function to add a vertex
void insertVertex(char data) {
    struct vertex* temp = (struct vertex*)malloc(sizeof(struct vertex));
    temp->data = data;
    temp->vnext = NULL;
    temp->estart = NULL;

    if (graphst == NULL) {
        graphst = temp;
    } else {
        struct vertex* vcurr = graphst;
        while (vcurr->vnext != NULL) {
            vcurr = vcurr->vnext;
        }
        vcurr->vnext = temp;
    }
}

// Function to add an edge with weight
void insertEdge(char source, char destination, int weight) {
    struct vertex* vcurr = graphst;
    struct vertex* sourceVertex = NULL;
    struct vertex* destVertex = NULL;

    while (vcurr != NULL) {
        if (vcurr->data == source) {
            sourceVertex = vcurr;
        } else if (vcurr->data == destination) {
            destVertex = vcurr;
        }
        vcurr = vcurr->vnext;
    }

    if (sourceVertex != NULL && destVertex != NULL) {
        struct edge* temp = (struct edge*)malloc(sizeof(struct edge));
        temp->tovertex = destVertex;
        temp->weight = weight;
        temp->enext = NULL;

        if (sourceVertex->estart == NULL) {
            sourceVertex->estart = temp;
        } else {
            struct edge* ecurr = sourceVertex->estart;
            while (ecurr->enext != NULL) {
                ecurr = ecurr->enext;
            }
            ecurr->enext = temp;
        }
    }
}

// Function to find the vertex with the minimum distance
char findMinDistanceVertex(bool processed[], int distance[], int numVertices) {
    int minDistance = INT_MAX;
    char minVertex;

    for (char i = 'A'; i <= 'Z'; i++) {
        if (!processed[i] && distance[i] < minDistance) {
            minDistance = distance[i];
            minVertex = i;
        }
    }

    return minVertex;
}

// Function to find the shortest path using Dijkstra's algorithm
void dijkstraShortestPath(char source, char destination) {
    if (graphst == NULL) {
        printf("Graph is empty\n");
        return;
    }

    int distance[128];  // To store the minimum distance from the source to each vertex
    bool processed[128];  // To keep track of processed vertices
    char parent[128];  // To store the parent of each vertex

    // Initialize distance, processed, and parent arrays
    for (char i = 'A'; i <= 'Z'; i++) {
        distance[i] = INT_MAX;
        processed[i] = false;
        parent[i] = -1;
    }

    distance[source] = 0;

    // Find the shortest path
    for (int count = 0; count < 128; count++) {
        char u = findMinDistanceVertex(processed, distance, 128);
        processed[u] = true;

        if (u == destination) {
            break;  // We have found the shortest path to the destination
        }

        for (struct vertex* v = graphst; v != NULL; v = v->vnext) {
            if (!processed[v->data]) {
                for (struct edge* e = v->estart; e != NULL; e = e->enext) {
                    if (distance[v->data] != INT_MAX &&
                        distance[v->data] + e->weight < distance[e->tovertex->data]) {
                        distance[e->tovertex->data] = distance[v->data] + e->weight;
                        parent[e->tovertex->data] = v->data;
                    }
                }
            }
        }
    }

    // Print the shortest path and distance
    if (distance[destination] == INT_MAX) {
        printf("No path found from %c to %c\n", source, destination);
    } else {
        printf("Shortest Path from %c to %c: ", source, destination);
        char vertex = destination;
        while (vertex != source) {
            printf("%c <- ", vertex);
            vertex = parent[vertex];
        }
        printf("%c\n", source);
        printf("Shortest Distance: %d\n", distance[destination]);
    }
}

int main() {
    // Example usage of the program
    insertVertex('A');
    insertVertex('B');
    insertVertex('C');
    insertVertex('D');
    insertVertex('E');
    insertVertex('F');
    insertVertex('G');
    insertVertex('H');
    insertVertex('I');
    insertVertex('J');
    insertVertex('K');
    insertVertex('L');

    insertEdge('A', 'B', 2);
    insertEdge('A', 'C', 3);
    insertEdge('A', 'D', 2);
    insertEdge('B', 'H', 5);
    insertEdge('C', 'G', 1);
    insertEdge('D', 'F', 3);
    insertEdge('D', 'E', 2);
    insertEdge('E', 'F', 2);
    insertEdge('H', 'G', 2);
    insertEdge('E', 'J', 6);
    insertEdge('G', 'I', 3);
    insertEdge('G', 'J', 2);
    insertEdge('I', 'J', 1);
    insertEdge('I', 'L', 1);
    insertEdge('L', 'J', 1);
    insertEdge('J', 'K', 5);

    char source = 'A';
    char destination = 'H';

    dijkstraShortestPath(source, destination);

    return 0;
}
