#include <stdio.h>
#include <string.h>

int hash(const char* key) {
    int hashVal = 0, len = strlen(key);
    for (int i = 0; i < len; i++) {
        hashVal += key[i];
    }
    return hashVal;
}

int main() {
    const char* myString = "cs"; // Replace with your own string
    int hashValue = hash(myString);
    printf("Hash value for '%s' is %d\n", myString, hashValue);
    return 0;
}