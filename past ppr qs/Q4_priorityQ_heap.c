/*a priority queue acts like a queue in that you dequeue an item by removing it from the front. however in a priority queue the logical order of items inside a queue is determined by their priority. the highest priority items are at front of the queue and the lowest priority are at the back. thus when you enqueue an item on the priority queue, the new item may move all the way to the front. 
you need to implement priority queue by choosing the approriate data structure. remember simple queue using list or array with a sorting function is not the answer to this problem.
you need to take input the name of the task and its priority from user to store in the queue. whenever task is removed from the queue the next highest priority task will be placed in the front. if two tasks with the same priority enter then the first entered process is removed first. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a task with a name and priority
struct Task {
    char name[100];
    int priority;
};

void swap(struct Task *a, struct Task *b) {
    struct Task temp = *a;
    *a = *b;
    *b = temp;
}

// Function to build a max heap
void buildMaxHeap(struct Task arr[], int n) {
    for (int i = 1; i < n; i++) {
        int child = i;
        while (child > 0) {
            int parent = (child - 1) / 2;
            if (arr[child].priority > arr[parent].priority) {
                swap(&arr[child], &arr[parent]);
                child = parent;
            } else {
                break;
            }
        }
    }
}

// Function to enqueue a task with a name and priority
void enqueue(struct Task **arr, int *size, const char *name, int priority) {
    struct Task newTask;
    strcpy(newTask.name, name);
    newTask.priority = priority;
    (*size)++;
    *arr = (struct Task *)realloc(*arr, (*size) * sizeof(struct Task));
    (*arr)[(*size) - 1] = newTask;
    buildMaxHeap(*arr, *size);
}

// Function to dequeue the highest priority task
struct Task dequeue(struct Task **arr, int *size) {
    struct Task emptyTask;
    strcpy(emptyTask.name, "Empty");
    emptyTask.priority = -1;
    
    if (*size <= 0) {
        return emptyTask;
    }

    struct Task highestPriorityTask = (*arr)[0];
    *size -= 1;
    if (*size > 0) {
        (*arr)[0] = (*arr)[*size];
        *arr = (struct Task *)realloc(*arr, *size * sizeof(struct Task));
        buildMaxHeap(*arr, *size);
    } else {
        free(*arr);
        *arr = NULL;
    }

    return highestPriorityTask;
}

int main() {
    struct Task *taskQueue = NULL;
    int size = 0;

    while (1) {
        int choice;
        printf("Menu:\n");
        printf("1. Enqueue a task\n");
        printf("2. Dequeue the highest priority task\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            char name[100];
            int priority;
            printf("Enter task name: ");
            scanf("%s", name);
            printf("Enter task priority: ");
            scanf("%d", &priority);
            enqueue(&taskQueue, &size, name, priority);
        } else if (choice == 2) {
            struct Task task = dequeue(&taskQueue, &size);
            if (task.priority != -1) {
                printf("Dequeued task: %s (Priority: %d)\n", task.name, task.priority);
            } else {
                printf("Queue is empty.\n");
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    if (taskQueue != NULL) {
        free(taskQueue);
    }

    return 0;
}
