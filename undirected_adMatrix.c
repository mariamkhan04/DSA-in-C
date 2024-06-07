#include <stdio.h>
#include <stdlib.h>

// Define the maximum number of vertices
#define MAX_VERTICES 100

int main() {

    // Declare the adjacency matrix
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];

    // Initialize the adjacency matrix to 0
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            adj_matrix[i][j] = 0;
        }
    }

    // Ask the user for the number of vertices
    int num_vertices;
    char answer;
    printf("Enter the number of vertices: ");
    scanf("%d", &num_vertices);

    // Iterate over all pairs of vertices and ask the user if there is an edge between them
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i; j < num_vertices; j++) {
            printf("Does an edge exist between %d and %d? (yes/no) ", i, j);
            scanf(" %c", &answer);
            if (answer == 'y' || answer == 'Y') {
                adj_matrix[i][j] = 1;
                adj_matrix[j][i] = 1; // For undirected graph, set the symmetric element
            }
        }
    }

    // Print the adjacency matrix
    printf("The adjacency matrix is:\n");
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }

    // Calculate the degree of each vertex
    int degrees[MAX_VERTICES];
    int totalDegree=0;
    for (int i = 0; i < num_vertices; i++) {
        degrees[i] = 0;
        for (int j = 0; j < num_vertices; j++) {
          if (adj_matrix[i][j] == 1) {
            // Increment the degree for each edge
            degrees[i]++;
            totalDegree++;
          }
        }
    }

    // Print the degree of each vertex
    printf("The degree of each vertex is:\n");
    for (int i = 0; i < num_vertices; i++) {
        printf("Vertex %d: %d\n", i, degrees[i]);
    }
    printf("Total degree of graph is: %d\n",totalDegree);

    return 0;
}
