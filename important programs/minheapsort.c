#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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

// Function to perform heap sort on a min heap
void minHeapSort(int arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);  // Swap root (min element) with the last element
        int parent = 0;
        int child = 1;

        while (child < i) {
            if (child + 1 < i && arr[child] > arr[child + 1]) {
                child++;
            }

            if (arr[parent] > arr[child]) {
                swap(&arr[parent], &arr[child]);
                parent = child;
                child = 2 * parent + 1;
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
    int minHeap[n];
    for (int i = 0; i < n; i++) {
        minHeap[i] = a[i];
    }
    buildMinHeap(minHeap, n);

    printf("Input Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("Min-Heap Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", minHeap[i]);
    }
    printf("\n");

    // Sort the max-heap and min-heap arrays

    minHeapSort(minHeap, n);

    printf("Sorted Min-Heap: ");
    for (int i = n-1; i >= 0; i--) {
        printf("%d ", minHeap[i]);
    }
    printf("\n");

    return 0;
}
