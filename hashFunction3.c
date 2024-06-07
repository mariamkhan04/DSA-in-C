#include<stdio.h>
#include<stdlib.h>
#include<string.h>

unsigned int hash_bernstein(const char* str) {
    unsigned int hash = 0; // Initial value
    while (*str) {
        hash = (hash * 33) ^ *str;
        str++;
    }
    return hash;
}
int main() {
    const char* myString = "cs"; // Replace with your own string
    int hashValue = hash_bernstein(myString);
    printf("Hash value for '%s' is %d\n", myString, hashValue);
    return 0;
}