#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct vertex {
    char data;
    struct vertex* vnext;
    struct edge* estart;
} *graphst = NULL;
struct edge {
    struct vertex* tovertex;
    struct edge* enext;
};

// Function to add a vertex
void insertVertex() {
    struct vertex* temp = (struct vertex*)malloc(sizeof(struct vertex));
    printf("Enter vertex: ");
    scanf(" %c", &temp->data);
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

// Function to add an edge
void insertEdge() {
    char source, destination;
    printf("Enter source: ");
    scanf(" %c", &source);
    printf("Enter destination: ");
    scanf(" %c", &destination);
    
    struct vertex* vcurr = graphst;
    while (vcurr != NULL) {
        if (vcurr->data == source) {
            struct edge* temp = (struct edge*)malloc(sizeof(struct edge));
            temp->tovertex = NULL;
            
            struct vertex* dcurr = graphst;
            while (dcurr != NULL) {
                if (dcurr->data == destination) {
                    temp->tovertex = dcurr;
                    break;
                }
                dcurr = dcurr->vnext;
            }
            
            if (temp->tovertex == NULL) {
                printf("Invalid destination to add\n");
                free(temp);
                return;
            }
            
            temp->enext = NULL;
            //to link an edge to source vertex
            if (vcurr->estart == NULL) {
                vcurr->estart = temp;
            } else {
                struct edge* ecurr = vcurr->estart;
                while (ecurr->enext != NULL) {
                    ecurr = ecurr->enext;
                }
                ecurr->enext = temp;
            }
            return;
        }
        vcurr = vcurr->vnext;
    }
    
    printf("Source vertex not found\n");
}
// Function to delete an edge
void deleteEdge() {
    char source, destination;
    printf("Enter source: ");
    scanf(" %c", &source);
    printf("Enter destination: ");
    scanf(" %c", &destination);
    
    struct vertex* vcurr = graphst;
    while (vcurr != NULL) {
        if (vcurr->data == source) {
            struct edge* prev = NULL;
            struct edge* ecurr = vcurr->estart;
            
            while (ecurr != NULL) {
                if (ecurr->tovertex->data == destination) {
                    // Found the edge, delete it
                    if (prev == NULL) {
                        // If the edge is the first one, update the start of the edge list
                        vcurr->estart = ecurr->enext;
                    } else {
                        prev->enext = ecurr->enext;
                    }
                    
                    free(ecurr); // Free the memory of the deleted edge
                    printf("Edge from %c to %c deleted\n", source, destination);
                    return;
                }
                
                prev = ecurr;
                ecurr = ecurr->enext;
            }
            
            printf("Edge from %c to %c not found\n", source, destination);
            return;
        }
        vcurr = vcurr->vnext;
    }
    
    printf("Source vertex not found\n");
}
// Function to delete a vertex
void deleteVertex() {
    char target;
    printf("Enter vertex to delete: ");
    scanf(" %c", &target);

    struct vertex* prev = NULL;
    struct vertex* vcurr = graphst;

    while (vcurr != NULL) {
        if (vcurr->data == target) {
            // Delete all incoming edges to the vertex
            struct vertex* v = graphst;
            while (v != NULL) {
                struct edge* eprev = NULL;
                struct edge* ecurr = v->estart;
                while (ecurr != NULL) {
                    if (ecurr->tovertex == vcurr) {
                        // Remove the edge
                        if (eprev == NULL) {
                            v->estart = ecurr->enext;
                        } else {
                            eprev->enext = ecurr->enext;
                        }
                        free(ecurr);
                        break;
                    } else {
                        eprev = ecurr;
                        ecurr = ecurr->enext;
                    }
                }
                v = v->vnext;
            }

            // Delete the vertex
            if (prev == NULL) {
                graphst = vcurr->vnext;
            } else {
                prev->vnext = vcurr->vnext;
            }
            free(vcurr);
            printf("Vertex %c deleted\n", target);
            return;
        }
        prev = vcurr;
        vcurr = vcurr->vnext;
    }

    printf("Vertex not found\n");
}
// Function to delete the entire graph
void deleteAll() {
    struct vertex* vcurr = graphst;

    while (vcurr != NULL) {
        struct vertex* vtmp = vcurr;
        vcurr = vcurr->vnext;
        free(vtmp);
    }

    graphst = NULL; // Set the graph start to NULL to indicate an empty graph
    printf("Graph deleted\n");
}
// Function to search for a vertex using depth-first search
bool depthFirstSearch(char target) {
    if (graphst == NULL) {
        printf("Graph is empty\n");
        return false;
    }

    struct vertex* startVertex = graphst;
    bool* visited = (bool*)malloc(sizeof(bool) * 128);
    for (int i = 0; i < 128; i++) {
        visited[i] = false;
    }
    bool cycle=false;

    struct vertex* stack[128];
    int path[128]; // To store the path
    int top = -1;

    // Push the startVertex onto the stack
    stack[++top] = startVertex;
    path[top] = startVertex->data;
    visited[startVertex->data] = true;

    while (top >= 0) {
        struct vertex* currentVertex = stack[top];
        int currentPathLength = top + 1;

        if (currentVertex->data == target) {
            printf("Vertex %c found\nPath: ", target);
            for (int i = 0; i < currentPathLength; i++) {
                printf("%c ", path[i]);
            }
            if (cycle)
            {
                printf("\nGraph has a cycle\n");
            }else{
                printf("\ngraph don't have a cycle\n");
            }
            
            printf("\n");
            free(visited);
            return true;
        }

        bool hasUnvisitedAdjacent = false; //to track whether the current vertex has unvisited adjacent vertices
        struct edge* currentEdge = currentVertex->estart;
        while (currentEdge != NULL) {
            struct vertex* adjacentVertex = currentEdge->tovertex;
            if (visited[adjacentVertex->data])
            {
                cycle=true;
            }
            if (!visited[adjacentVertex->data]) {
                stack[++top] = adjacentVertex;
                path[top] = adjacentVertex->data;
                visited[adjacentVertex->data] = true;
                hasUnvisitedAdjacent = true;
                break; // Explore the adjacent vertex
            }
            currentEdge = currentEdge->enext;
        }

        if (!hasUnvisitedAdjacent) {
            // Backtrack if there are no unvisited adjacent vertices
            --top;
        }
    }

    printf("Vertex %c not found\n", target);
    free(visited);
    return false;
}
bool breadthFirstSearch(char target) {
    if (graphst == NULL) {
        printf("Graph is empty\n");
        return false;
    }

    bool* visited = (bool*)malloc(sizeof(bool) * 128); // Assuming ASCII characters
    for (int i = 0; i < 128; i++) {
        visited[i] = false;
    }
    bool cycle=false;
    struct vertex* queue[128]; // Assuming ASCII characters
    int front = 0;
    int rear = 0;

    // Push the startVertex onto the queue
    queue[rear++] = graphst;
    visited[graphst->data] = true;
    // Create an array to store the path
    struct vertex* path[128];

    while (front < rear) {
        struct vertex* currentVertex = queue[front++];
        // Store the current vertex in the path
        path[front - 1] = currentVertex; //stores the currentVertex in the path array. It uses front - 1 as the index to store the currentVertex in the path array because front has already been incremented earlier to dequeue the vertex.
        
        if (currentVertex->data == target) {
            printf("Vertex %c found\nPath ", target);
            for (int i = 0; i < front; i++) {
                printf("%c ", path[i]->data);
            }
            if (cycle)
            {
                printf("Graph has cycle\n");
            }else{
                printf("graph dont have a cycle\n");
            }
            
            free(visited);
            return true;
        }

        // Iterate through adjacent vertices and enqueue them if not visited
        struct edge* currentEdge = currentVertex->estart;
        while (currentEdge != NULL) {
            struct vertex* adjacentVertex = currentEdge->tovertex;
            if(visited[adjacentVertex->data]){
                cycle=true;
            }
            if (!visited[adjacentVertex->data]) {
                queue[rear++] = adjacentVertex;
                visited[adjacentVertex->data] = true;
            }
            currentEdge = currentEdge->enext;
        }
    }

    printf("Vertex %c not found\n", target);
    free(visited);
    return false;
}
// Function to print out-degree
void printOutDegree() {
    char source;
    int outDegree = 0;
    printf("Enter source: ");
    scanf(" %c", &source);
    
    struct vertex* vcurr = graphst;
    while (vcurr != NULL) {
        if (vcurr->data == source) {
            struct edge* ecurr = vcurr->estart;
            while (ecurr != NULL) {
                outDegree++;
                ecurr = ecurr->enext;
            }
            
            printf("Out-Degree is %d\n", outDegree);
            return;
        }
        vcurr = vcurr->vnext;
    }
    
    printf("Source vertex not found\n");
}

// Function to print in-degree
void printInDegree() {
    char vertex;
    int inDegree = 0;
    printf("Enter vertex: ");
    scanf(" %c", &vertex);
    
    struct vertex* vcurr = graphst;
    while (vcurr != NULL) {
        struct edge* ecurr = vcurr->estart;
        while (ecurr != NULL) {
            if (ecurr->tovertex->data == vertex) {
                inDegree++;
            }
            ecurr = ecurr->enext;
        }
        vcurr = vcurr->vnext;
    }
    
    printf("In-Degree is %d\n", inDegree);
}

// Function to print vertices and edges
void printVerticesAndEdges() {
    struct vertex* vcurr = graphst;
    int totalDegrees=0;
    while (vcurr != NULL) {
        printf("Vertex %c:  ", vcurr->data);
        struct edge* ecurr = vcurr->estart;
        
        if (ecurr == NULL) {
            printf("no edges\n");
        } else {
            while (ecurr != NULL) {
                printf("%c\t", ecurr->tovertex->data);
                totalDegrees++;
                ecurr = ecurr->enext;
            }
        }
        
        printf("\n");
        vcurr = vcurr->vnext;
    }
    printf("Total degrees are: %d\n",totalDegrees);
}

int main() {
    int choice, lengthList;
    char tosearchVertex;
    bool flag = true;
    
    while (flag) {
        printf("Options\n1. Insert Vertex\n2. Insert Edge\n3. Print Out-degree\n4. Print In-Degree\n5. Print All\n6. deleteEdge\n7. deleteVertex\n8. DeleteGraph\n9. depthFirstSearch\n10. breadthFirstSearch\n11. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the number of vertices: ");
                scanf("%d", &lengthList);
                for (int i = 0; i < lengthList; i++) {
                    insertVertex();
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
                deleteEdge();
                break;
            case 7:
                deleteVertex();
                break; 
            case 8:
                deleteAll();
                break;
             case 9:
                printf("Enter the vertex to search: ");
                scanf(" %c", &tosearchVertex);
                depthFirstSearch(tosearchVertex);
                break;
            case 10:
                printf("Enter the vertex to search: ");
                scanf(" %c", &tosearchVertex);
                breadthFirstSearch(tosearchVertex);
                break;
            case 11:
                flag = false;
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    
    return 0;
}