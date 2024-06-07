#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h> //for defining various implementation-specific limits such as the maximum and minimum values for various data types.

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
    struct vertex* vcurr = graphst; //points to first vertex in the graph
    struct vertex* sourceVertex = NULL; //to point to source vertex
    struct vertex* destVertex = NULL; //to point to destination vertex

    while (vcurr != NULL) {
        if (vcurr->data == source) {
            sourceVertex = vcurr;
        } else if (vcurr->data == destination) {
            destVertex = vcurr;
        }
        vcurr = vcurr->vnext;
    }
//If both source and destination vertices were found in the previous loop, it means that the graph contains valid source and destination vertices.
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

        // Adding the reverse edge as well since it's an undirected graph
        temp = (struct edge*)malloc(sizeof(struct edge));
        temp->tovertex = sourceVertex;
        temp->weight = weight;
        temp->enext = NULL;

        if (destVertex->estart == NULL) {
            destVertex->estart = temp;
        } else {
            struct edge* ecurr = destVertex->estart;
            while (ecurr->enext != NULL) {
                ecurr = ecurr->enext;
            }
            ecurr->enext = temp;
        }
    }
}
// Depth-First Search (DFS) function
void dfs(char vertex, char visited[128]) {
    visited[vertex] = true;
    struct vertex* vcurr = graphst;
    while (vcurr != NULL) {
        if (!visited[vcurr->data]) {
            struct edge* e = vcurr->estart;
            while (e != NULL) {
                if (e->tovertex->data == vertex) {
                    dfs(vcurr->data, visited);
                }
                e = e->enext;
            }
        }
        vcurr = vcurr->vnext;
    }
}
// Function to check if the graph is connected
bool isConnected() {
    if (graphst == NULL) {
        return false;
    }

    char visited[128]; // To keep track of visited vertices
    for (int i = 0; i < 128; i++) {
        visited[i] = false;
    }

    // Perform a Depth-First Search (DFS) starting from the first vertex
    struct vertex* startVertex = graphst;
    dfs(startVertex->data, visited);

    // Check if all vertices are visited
    for (struct vertex* v = graphst; v != NULL; v = v->vnext) {
        if (!visited[v->data]) {
            return false;
        }
    }

    return true;
}
// Function to find the minimum spanning tree using Prim's algorithm
int primMST() {
    if (graphst == NULL) {
        printf("Graph is empty\n");
        return 0;
    }

    char included[128]; // To keep track of included vertices in mst
    int key[128];       // To store the key value of each vertex The key values represent the minimum edge weight from a vertex to the mst
    char parent[128];   // To store the parent of each vertex in mst

    // Initialize included, key, and parent arrays
    for (int i = 0; i < 128; i++) {
        included[i] = false;
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    // The first vertex in mst is the starting vertex.The key value of the starting vertex (the first vertex in the graph) is set to 0. 
    key[graphst->data] = 0;

    int totalCost = 0; // To store the total cost of the minimum spanning tree

    for (struct vertex* u = graphst; u != NULL; u = u->vnext) {
        char minVertex = 0; // to store the vertex with the minimum key value from the set of vertices not yet included in the MST
        int minKey = INT_MAX; // store the minimum key value found during the search.
        for (struct vertex* v = graphst; v != NULL; v = v->vnext) {
            if (!included[v->data] && key[v->data] < minKey) {
                minVertex = v->data;
                minKey = key[v->data];
            }
        }

        included[minVertex] = true; //After we find the vertex with the minimum key value, we mark it as included in the MST by setting included[minVertex] to true.

        // Update key values of adjacent vertices if they are not included in the MST
        struct vertex* uVertex = NULL; // store the vertex in the graph corresponding to minVertex
        for (struct vertex* v = graphst; v != NULL; v = v->vnext) {
            if (v->data == minVertex) {
                uVertex = v;
                break;
            }
        }
//This loop iterates through all edges that originate from the vertex uVertex
        for (struct edge* e = uVertex->estart; e != NULL; e = e->enext) { //we check if the destination vertex of the current edge e has not been included in the MST and if the weight of the edge is less than the current key value of the destination vertex.
            if (!included[e->tovertex->data] && e->weight < key[e->tovertex->data]) {
                parent[e->tovertex->data] = uVertex->data;
                //We update the parent array to mark uVertex as the parent of the destination vertex
                key[e->tovertex->data] = e->weight;
            }
        }
    }

    // Print the minimum spanning tree
    printf("Minimum Spanning Tree:\n");
    for (char i = 'A'; i <= 'Z'; i++) {
        if (parent[i] != -1) { //check each vertex to see if it has a parent (indicating that it's part of the MST). If it does, we print the edge and its weight.
            printf("Edge: %c - %c, Weight: %d\n", parent[i], i, key[i]);
            totalCost += key[i];
        }
    }

    return totalCost;
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

    if (isConnected()) {
        int minCost = primMST();
        printf("Minimum Cost of the Minimum Spanning Tree: %d\n", minCost);
    } else {
        printf("The graph is not connected. Prim's algorithm cannot be applied.\n");
    }

    return 0;
}