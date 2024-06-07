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
// Function to perform heap sort on a max heap
void maxHeapSort(int arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);  // Swap root (max element) with the last element
        int parent = 0;
        int child = 1;

        while (child < i) {
            if (child + 1 < i && arr[child] < arr[child + 1]) {
                child++;
            }

            if (arr[parent] < arr[child]) {
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
    int a[] = {20,30,80,10,50,25,18,97,40};
    int n = sizeof(a) / sizeof(a[0]);

    // Creating a copy of the input array to build max and min heaps
    int maxHeap[n];
    for (int i = 0; i < n; i++) {
        maxHeap[i] = a[i];
    }

    buildMaxHeap(maxHeap, n);

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

// Sort the max-heap and min-heap arrays
    maxHeapSort(maxHeap, n);
    printf("Sorted Max-Heap: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", maxHeap[i]);
    }
    printf("\n");
    return 0;
}