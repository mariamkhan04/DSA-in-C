#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Structure for a vertex
struct vertex {
    int data;  // Change data type to int
    bool visited;
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
void insertVertex(int data) {
    struct vertex* temp = (struct vertex*)malloc(sizeof(struct vertex));
    temp->data = data;
    temp->visited = false;
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
void insertEdge(int source, int destination, int weight) {
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

// Depth-First Search (DFS) function
void dfs(struct vertex* v) {
    if (v == NULL) {
        return;
    }

    v->visited = true;
    printf("%d ", v->data);

    struct edge* ecurr = v->estart;
    while (ecurr != NULL) {
        if (!(ecurr->tovertex->visited)) {
            dfs(ecurr->tovertex);
        }
        ecurr = ecurr->enext;
    }
}

bool isConnected() {
    if (graphst == NULL) {
        return false;
    }

    dfs(graphst);

    struct vertex* vcurr = graphst;
    while (vcurr != NULL) {
        if (!vcurr->visited) {
            return false;
        }
        vcurr = vcurr->vnext;
    }

    return true;
}
int primMST() {
    if (graphst == NULL) {
        printf("Graph is empty\n");
        return 0;
    }

    int included[100];
    int key[100];
    int parent[100];

    for (int i = 0; i < 100; i++) {
        included[i] = 0;
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[0] = 0; // Start from the first vertex (index 0)

    int totalCost = 0;

    for (int count = 0; count < 100; count++) {
        int minVertex = -1;
        int minKey = INT_MAX;

        for (int i = 0; i < 100; i++) {
            if (!included[i] && key[i] < minKey) {
                minVertex = i;
                minKey = key[i];
            }
        }

        if (minVertex == -1) {
            break; // No more vertices to include
        }

        included[minVertex] = 1;

        struct vertex* uVertex = graphst;
        while (uVertex->data != minVertex) {
            uVertex = uVertex->vnext;
        }

        struct edge* e = uVertex->estart;
        while (e != NULL) {
            int v = e->tovertex->data;
            if (!included[v] && e->weight < key[v]) {
                parent[v] = minVertex;
                key[v] = e->weight;
            }
            e = e->enext;
        }
    }

    printf("Minimum Spanning Tree:\n");
    for (int i = 1; i < 100; i++) {
        if (parent[i] != -1) {
            printf("Edge: %d - %d, Weight: %d\n", parent[i], i, key[i]);
            totalCost += key[i];
        }
    }

    return totalCost;
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    for (int i = 0; i < numVertices; i++) {
        int vertexData;
        printf("Enter the vertex value: ");
        scanf("%d", &vertexData);
        insertVertex(vertexData);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        int source, destination, weight;
        printf("Enter source vertex: ");
        scanf("%d", &source);
        printf("Enter destination vertex: ");
        scanf("%d", &destination);
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
