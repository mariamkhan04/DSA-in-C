#include<stdio.h>
#include<stdlib.h> 

// perform the bubble sort
void bubbleSort(int array[], int size) {
    
    int totalSwaps = 0; // Counter to track the number of swaps
  
  // loop to access each array element
  for (int i = 0; i < size - 1; i++) {
    
    // check if swapping occurs  
    int swapped = 0;

    // loop to compare array elements
    for (int j = 0; j < size - i - 1; j++) {
      
      // compare two array elements
      // change > to < to sort in descending order
      if (array[j] > array[j + 1]) {
        
        // swapping occurs if elements
        // are not in the intended order
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        
        swapped = 1;
        totalSwaps++;
      }
    }
    
    // no swapping means the array is already sorted
    // so no need for further comparison
    if (swapped == 0) {
      break;
    }
    }
     // Print the total number of swaps after sorting is done
  printf("Total swaps during sorting: %d\n", totalSwaps);
}

// print array
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

// main method
int main() {
  int data[] = {-2, 45, 0, 11, -9};
  
  // find the array's length
  int size = sizeof(data) / sizeof(data[0]);

  bubbleSort(data, size);
  
  printf("Sorted Array in Ascending Order:\n");
  printArray(data, size);
}