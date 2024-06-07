#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a task
struct Task {
    char name[100];
    int priority;
};

// Structure for the priority queue
struct PriorityQueue {
    struct Task* tasks;
    int capacity;
    int size;
};

// Function to create a new priority queue
struct PriorityQueue* createPriorityQueue(int capacity) {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->tasks = (struct Task*)malloc(capacity * sizeof(struct Task));
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

// Helper function to swap two tasks
void swap(struct Task* a, struct Task* b) {
    struct Task temp = *a;
    *a = *b;
    *b = temp;
}

// Function to enqueue a task with its priority
void enqueue(struct PriorityQueue* pq, const char* name, int priority) {
    if (pq->size == pq->capacity) {
        printf("Priority queue is full. Cannot enqueue more tasks.\n");
        return;
    }
    
    struct Task newTask;
    strcpy(newTask.name, name);
    newTask.priority = priority;

    pq->tasks[pq->size] = newTask;
    int current = pq->size;
    int parent = (current - 1) / 2;

    // Heapify: Move the newly added task to its correct position based on priority
    while (current > 0 && pq->tasks[current].priority > pq->tasks[parent].priority) {
        swap(&pq->tasks[current], &pq->tasks[parent]);
        current = parent;
        parent = (current - 1) / 2;
    }

    pq->size++;
}

// Function to dequeue the task with the highest priority
void dequeue(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty. Cannot dequeue.\n");
        return;
    }

    // Swap the first and last tasks
    swap(&pq->tasks[0], &pq->tasks[pq->size - 1]);
    pq->size--;

    int current = 0;
    int left, right, largest;

    // Heapify: Move the task at the front to its correct position
    while (1) {
        left = 2 * current + 1;
        right = 2 * current + 2;
        largest = current;

        if (left < pq->size && pq->tasks[left].priority > pq->tasks[largest].priority) {
            largest = left;
        }
        if (right < pq->size && pq->tasks[right].priority > pq->tasks[largest].priority) {
            largest = right;
        }

        if (largest != current) {
            swap(&pq->tasks[current], &pq->tasks[largest]);
            current = largest;
        } else {
            break;
        }
    }
}

// Function to print the tasks in the priority queue
void printPriorityQueue(struct PriorityQueue* pq) {
    printf("Priority Queue (Front to Back):\n");
    for (int i = 0; i < pq->size; i++) {
        printf("Task: %s, Priority: %d\n", pq->tasks[i].name, pq->tasks[i].priority);
    }
    printf("\n");
}

// Function to free the allocated memory
void freePriorityQueue(struct PriorityQueue* pq) {
    free(pq->tasks);
    free(pq);
}

int main() {
    struct PriorityQueue* pq = createPriorityQueue(100);

    while (1) {
        printf("Enter the name of the task (or 'quit' to exit): ");
        char name[100];
        scanf("%s", name);
        if (strcmp(name, "quit") == 0) {
            break;
        }

        printf("Enter the priority of the task: ");
        int priority;
        scanf("%d", &priority);

        enqueue(pq, name, priority);
        printPriorityQueue(pq);
    }

    while (pq->size > 0) {
        printf("Dequeueing task: %s\n", pq->tasks[0].name);
        dequeue(pq);
        printPriorityQueue(pq);
    }

    freePriorityQueue(pq);

    return 0;
}
