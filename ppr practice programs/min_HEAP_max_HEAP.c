#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to build a max heap
void buildMaxHeap(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int child = i;
        while (child > 0) {
            int parent = (child - 1) / 2;
            if (arr[child] > arr[parent]) {
                swap(&arr[child], &arr[parent]);
                child = parent;
            } else {
                break;
            }
        }
    }
}

// Function to build a min heap
void buildMinHeap(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int child = i;
        while (child > 0) {
            int parent = (child - 1) / 2;
            if (arr[child] < arr[parent]) {
                swap(&arr[child], &arr[parent]);
                child = parent;
            } else {
                break;
            }
        }
    }
}

int main() {
    int a[] = {75, 19, 20, 18, 85, 95, 55, 29, 17, 9};
    int n = sizeof(a) / sizeof(a[0]);

    // Creating a copy of the input array to build max and min heaps
    int maxHeap[n];
    int minHeap[n];
    for (int i = 0; i < n; i++) {
        maxHeap[i] = a[i];
        minHeap[i] = a[i];
    }

    buildMaxHeap(maxHeap, n);
    buildMinHeap(minHeap, n);

    printf("Input Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("Max-Heap Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", maxHeap[i]);
    }
    printf("\n");

    printf("Min-Heap Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", minHeap[i]);
    }
    printf("\n");

    return 0;
}
