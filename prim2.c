#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h> //INT_MAX KE USE KELIYE

// Structure for a vertex
struct vertex {
    char data;
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
void insertVertex(char data) {
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
void dfs(struct vertex* v) {
    if (v == NULL) {
        return;
    }

    v->visited = true;
    printf("%c ", v->data);

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

        //LOOP TO FIND VERTEX WITH MINIMUM KEY VALUE
        for (struct vertex* v = graphst; v != NULL; v = v->vnext) {
            if (!included[v->data] && key[v->data] < minKey) {
                minVertex = v->data;
                minKey = key[v->data];
            }
        }

        included[minVertex] = true; //After we find the vertex with the minimum key value, we mark it as included in the MST by setting included[minVertex] to true.

        //Ek uVertex POINTER define kiya jata hai jo minVertex se corresponding vertex ko POINT karega.
        struct vertex* uVertex = NULL; // store the vertex in the graph corresponding to minVertex
        for (struct vertex* v = graphst; v != NULL; v = v->vnext) {
            if (v->data == minVertex) {
                uVertex = v;
                break;
            }
        }
//This loop iterates through all edges that originate from the vertex uVertex. uVertex se shuru hone wale har edge ko check kiya jata hai.
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
// Enter the number of vertices: 10
// Enter the vertex label (A, B, C, etc.): A
// Enter the vertex label (A, B, C, etc.): B
// Enter the vertex label (A, B, C, etc.): C
// Enter the vertex label (A, B, C, etc.): D
// Enter the vertex label (A, B, C, etc.): E
// Enter the vertex label (A, B, C, etc.): F
// Enter the vertex label (A, B, C, etc.): G
// Enter the vertex label (A, B, C, etc.): H
// Enter the vertex label (A, B, C, etc.): I
// Enter the vertex label (A, B, C, etc.): J
// Enter the number of edges: 13
// Enter source vertex: A
// Enter destination vertex: B
// Enter edge weight: 9
// Enter source vertex: A
// Enter destination vertex: C
// Enter edge weight: 9
// Enter source vertex: A
// Enter destination vertex: D
// Enter edge weight: 8
// Enter source vertex: B
// Enter destination vertex: E
// Enter edge weight: 5
// Enter source vertex: C
// Enter destination vertex: F
// Enter edge weight: 4
// Enter source vertex: B
// Enter destination vertex: F
// Enter edge weight: 3
// Enter source vertex: D
// Enter destination vertex: F
// Enter edge weight: 5
// Enter source vertex: D
// Enter destination vertex: G
// Enter edge weight: 5
// Enter source vertex: D
// Enter destination vertex: J
// Enter edge weight: 6
// Enter source vertex: E
// Enter destination vertex: H
// Enter edge weight: 7
// Enter source vertex: G
// Enter destination vertex: H
// Enter edge weight: 7
// Enter source vertex: J
// Enter destination vertex: I
// Enter edge weight: 7
// Enter source vertex: I
// Enter destination vertex: H
// Enter edge weight: 3
// A B E H G D F C J I Minimum Spanning Tree:
// Edge: F - B, Weight: 3
// Edge: F - C, Weight: 4
// Edge: A - D, Weight: 8
// Edge: B - E, Weight: 5
// Edge: D - F, Weight: 5
// Edge: D - G, Weight: 5
// Edge: E - H, Weight: 7
// Edge: H - I, Weight: 3
// Edge: D - J, Weight: 6
// Minimum Cost of the Minimum Spanning Tree: 46