/*a big integer is an integer whose digits are stored as elements in a data structure:
1. represent integer with one digit per ode of a linked list
2. Compute addition, subtraction, multiplication of two integers stored as big integers the resultant should also be stored as big integer 
Note: Do remember you are required to compute using the digits stored in linked list not as a complete integer.*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node with a given digit
struct Node* createNode(int digit) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = digit;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new digit at the end of a big integer (linked list)
struct Node* insertDigit(struct Node* list, int digit) {
    struct Node* newDigit = createNode(digit);

    if (list == NULL) {
        return newDigit;
    } else {
        struct Node* current = list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newDigit;
        return list;
    }
}

// Function to print a big integer represented as a linked list
void printBigInteger(struct Node* num) {
    if (num == NULL) {
        printf("0\n");
        return;
    }

    while (num != NULL) {
        printf("%d", num->data);
        num = num->next;
    }
    printf("\n");
}

// Function to add two big integers
struct Node* add(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry != 0) {
        int sum = carry;

        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }

        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum %= 10;

        result = insertDigit(result, sum);
    }

    return result;
}

// Function to subtract two big integers
struct Node* subtract(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    int borrow = 0;

    while (num1 != NULL || num2 != NULL) {
        int diff = borrow;

        if (num1 != NULL) {
            diff += num1->data;
            num1 = num1->next;
        }

        if (num2 != NULL) {
            diff -= num2->data;
            num2 = num2->next;
        }

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        result = insertDigit(result, diff);
    }

    // Remove leading zeros in the result
    while (result != NULL && result->data == 0) {
        struct Node* temp = result;
        result = result->next;
        free(temp);
    }

    return result;
}

// Function to multiply a big integer by a single digit
struct Node* multiply(struct Node* num, int digit) {
    struct Node* result = NULL;
    int carry = 0;

    while (num != NULL || carry != 0) {
        int product = carry;

        if (num != NULL) {
            product += num->data * digit;
            num = num->next;
        }

        carry = product / 10;
        product %= 10;

        result = insertDigit(result, product);
    }

    return result;
}

int main() {
    struct Node* num1 = NULL;
    struct Node* num2 = NULL;

    int digit;
    printf("Enter the first big integer (Enter -1 to end input):\n");
    while (1) {
        scanf("%d", &digit);
        if (digit == -1) {
            break;
        }
        num1 = insertDigit(num1, digit);
    }

    printf("Enter the second big integer (Enter -1 to end input):\n");
    while (1) {
        scanf("%d", &digit);
        if (digit == -1) {
            break;
        }
        num2 = insertDigit(num2, digit);
    }

    printf("Number 1: ");
    printBigInteger(num1);
    printf("Number 2: ");
    printBigInteger(num2);

    struct Node* sum = add(num1, num2);
    printf("Sum: ");
    printBigInteger(sum);

    struct Node* difference = subtract(num1, num2);
    printf("Difference: ");
    printBigInteger(difference);

    struct Node* product = multiply(num1, 2);
    printf("Product: ");
    printBigInteger(product);

    // Free the memory used by linked lists
    while (num1 != NULL) {
        struct Node* temp = num1;
        num1 = num1->next;
        free(temp);
    }
    while (num2 != NULL) {
        struct Node* temp = num2;
        num2 = num2->next;
        free(temp);
    }
    while (sum != NULL) {
        struct Node* temp = sum;
        sum = sum->next;
        free(temp);
    }
    while (difference != NULL) {
        struct Node* temp = difference;
        difference = difference->next;
        free(temp);
    }
    while (product != NULL) {
        struct Node* temp = product;
        product = product->next;
        free(temp);
    }

    return 0;
}
