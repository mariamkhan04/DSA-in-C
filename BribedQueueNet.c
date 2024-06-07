#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to implement Bubble Sort
void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap the elements if they are in the wrong order
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        // If no two elements were swapped in the inner loop, the array is sorted
        if (!swapped) {
            break;
        }
    }
}

// Function to count bribes in the queue
int BribedQueue(int arr[], int n) {
    int bribes = 0;

    // Loop through the queue to find bribes
    for (int i = 0; i < n; i++) {
        // If the element is not in its original position, it's bribed
        if (arr[i] != i + 1) {
            // Calculate the number of positions the element moved from its original position
            int diff = arr[i] - (i + 1);

            // Check if the number of bribes is more than 2 (invalid)
            if (diff > 2) {
                printf("Invalid queue! More than 2 bribes for a person.\n");
                return -1;
            }

            // Increment the total number of bribes
            bribes += diff;
        }
    }

    return bribes;
}

int main() {
    int n;
    FILE *file;
    
    // Open the file for reading
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    
    // Read the length of the array from the file
    fscanf(file, "%d", &n);
    
    // Allocate memory for the array dynamically
    int *arr = (int *)malloc(n * sizeof(int));
    
    // Read the elements of the array from the file
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    
    // Close the file
    fclose(file);
    
    // Sort the queue using Bubble Sort
    bubbleSort(arr, n);

    // Count the number of bribes in the queue
    int bribes = BribedQueue(arr, n);

    // Check if there was an error while counting bribes
    if (bribes == -1) {
        free(arr); // Free the allocated memory
        return 1;
    }

    // Print the result
    printf("Number of bribes: %d\n", bribes);

    // Free the allocated memory
    free(arr);

    return 0;
}
