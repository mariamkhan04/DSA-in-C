#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Structure for a vertex
struct vertex {
    char data;
    struct vertex* vnext;
    struct edge* estart;
};

// Structure for an edge
struct edge {
    struct vertex* tovertex;
    int weight;
    struct edge* enext;
};

// Structure for an edge in Kruskal's algorithm
struct kruskalEdge {
    char source;
    char destination;
    int weight;
};

struct vertex* graphst = NULL;

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
        temp->enext = sourceVertex->estart;
        sourceVertex->estart = temp;

        // Adding the reverse edge as well since it's an undirected graph
        temp = (struct edge*)malloc(sizeof(struct edge));
        temp->tovertex = sourceVertex;
        temp->weight = weight;
        temp->enext = destVertex->estart;
        destVertex->estart = temp;
    }
}

// Depth-First Search (DFS) function
void dfs(struct vertex* v, char visited[128]) {
    visited[v->data] = true;
    struct edge* e = v->estart;
    while (e != NULL) {
        if (!visited[e->tovertex->data]) {
            dfs(e->tovertex, visited);
        }
        e = e->enext;
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
    dfs(graphst, visited);

    // Check if all vertices are visited
    struct vertex* v = graphst;
    while (v != NULL) {
        if (!visited[v->data]) {
            return false;
        }
        v = v->vnext;
    }

    return true;
}

// Function to compare edges for sorting in ascending order
int compareEdges(const void* a, const void* b) {
    return ((struct kruskalEdge*)a)->weight - ((struct kruskalEdge*)b)->weight;
}

// Function to check if two vertices are part of the same component
bool isSameComponent(char v1, char v2, int* component) {
    return component[v1] == component[v2];
}

// Function to union two components
void unionComponents(char v1, char v2, int* component) {
    int componentV1 = component[v1];
    int componentV2 = component[v2];
    for (int i = 0; i < 128; i++) {
        if (component[i] == componentV2) {
            component[i] = componentV1;
        }
    }
}

// Kruskal's Minimum Spanning Tree algorithm
void kruskalMST() {
    int totalMSTCost;
    // Check if the graph is connected
    if (!isConnected()) {
        printf("Graph is not connected, MST cannot be found.\n");
        return;
    }

    struct kruskalEdge edges[1000]; // Array to store all edges
    int edgeCount = 0;

    // Traverse the graph and add all edges to the 'edges' array
    struct vertex* v = graphst;
    while (v != NULL) {
        struct edge* e = v->estart;
        while (e != NULL) {
            if (v->data < e->tovertex->data) {  //to avoid duplicate edges eg: ba is duplicate of ab
                edges[edgeCount].source = v->data;
                edges[edgeCount].destination = e->tovertex->data;
                edges[edgeCount].weight = e->weight;
                edgeCount++;
            }
            e = e->enext;
        }
        v = v->vnext;
    }

    // Sort the edges in ascending order of weight
    qsort(edges, edgeCount, sizeof(struct kruskalEdge), compareEdges);//sizeof(struct kruskalEdge) array mai har element ka size
    //compareEdges function to compare two edges(jiska weight kam hua it will come first in sorted arr)

    // Initialize components for each vertex
    int component[128]; //component array me har vertex ke liye ek alag component number initialize hota hai
    for (int i = 0; i < 128; i++) {
        component[i] = i;
    }
    totalMSTCost = 0; // Initialize the total cost of MST
    printf("Minimum Spanning Tree (Kruskal's Algorithm):\n");
    //s loop me, sorted edges ko ek ek karke check kiya jata hai. Agar ek edge ko add karne se cycle nahi banta, toh us edge ko MST me shamil kiya jata hai, uska weight print kiya jata hai, aur unionComponents function se dono vertices ko ek hi component me merge kiya jata hai. 
    for (int i = 0; i < edgeCount; i++) {
        char source = edges[i].source;
        char destination = edges[i].destination;
        int weight = edges[i].weight;

        // Check if adding this edge forms a cycle
        if (!isSameComponent(source, destination, component)) {
            printf("%c - %c: %d\n", source, destination, weight);
            unionComponents(source, destination, component);
            totalMSTCost += weight; // Update the total cost
        }
    }
    printf("Total Cost of MST: %d\n", totalMSTCost); // Print the total cost
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

int main() {
    int choice;
    char source, destination, data;
    int weight;
    
    while (1) {
        printf("1. Insert a vertex\n");
        printf("2. Insert an edge\n");
        printf("3. Display Minimum Spanning Tree\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the vertex data: ");
                scanf(" %c", &data);
                insertVertex(data);
                break;
                
            case 2:
                printf("Enter source vertex: ");
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
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
