#include <stdio.h>

int main() {
    for (int i = 0; i < 5; i++) {
        if (i == 3) {
            
            // Exit the loop when i equals 3
            break;  
        }
        printf("%d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < 5; i++) {
        if (i == 3) {
            
            // Skip the current iteration
            // when i equals 3
            continue;  
        }
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < 5; i++) {
        if (i == 3) {
            
            // Jump to the skip label when
            // i equals 3
            goto skip;
        }
        printf("%d ", i);
    }
    
skip:
    printf("\nJumped to the 'skip' label %s",
    "when i equals 3.");

    return 0;
}
