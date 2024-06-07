#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <stdio.h>
#include <stdio.h>

int hash_function(float key, int table_size) {
  return floor(key);
}

int main() {
  float key = 12.85;
  int table_size = 10;
  int result = hash_function(key, table_size);

  // Cast the integer value to a pointer to a string.
  char *string_result = (char *)malloc(sizeof(char) * 10);
  sprintf(string_result, "%d", result);

  printf("%s\n", string_result);

  free(string_result);

  return 0;
}

