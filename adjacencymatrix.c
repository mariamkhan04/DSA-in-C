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
        for (int j = 0; j < num_vertices; j++) {
            printf("Does an edge exists between %d and %d? (yes/no) ",i,j);
            scanf(" %c",&answer);
            if (answer=='y' || answer=='Y')
            {
                adj_matrix[i][j] = 1;
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
        // Calculate the in-degree and out-degree of each vertex
    int in_degree[MAX_VERTICES];
    int out_degree[MAX_VERTICES];

    for (int i = 0; i < num_vertices; i++) {
        in_degree[i] = 0;
        out_degree[i] = 0;
        for (int j = 0; j < num_vertices; j++) {
            in_degree[i] += adj_matrix[j][i];
            out_degree[i] += adj_matrix[i][j];
        }
    }

    // Print the in-degree and out-degree of each vertex
    printf("The in-degree and out-degree of each vertex is:\n");
    for (int i = 0; i < num_vertices; i++) {
        printf("Vertex %d: In-degree=%d, Out-degree=%d\n", i, in_degree[i], out_degree[i]);
    }
    return 0;
}
