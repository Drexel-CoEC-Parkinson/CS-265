#include <stdio.h>

int main() {
  int myNumbers[] = {3, -1, 7, 0, 9};
  int length = sizeof(myNumbers) / sizeof(myNumbers[0]);
  int i;

  for (i = 0; i < length; i++) {
    if (myNumbers[i] < 0) {
      continue; // skip negative numbers
    }
    if (myNumbers[i] == 0) {
      break; // stop loop when zero is found
    }
    printf("%d\n", myNumbers[i]);
  }  
  
  return 0;
}
