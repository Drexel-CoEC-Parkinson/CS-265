#include <stdio.h>

int main() {
    // Outer loop runs 3 times
    for (int i = 0; i < 3; i++) {
        
        // Inner loop runs 2 times for each
        // outer loop iteration
        for (int j = 0; j < 2; j++) {
            printf("i = %d, j = %d\n", i, j);
        }
    }
    return 0;
}
