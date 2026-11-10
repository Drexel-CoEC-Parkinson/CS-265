#include <stdio.h>

int main() {
    
    // variable to be used in switch statement
    int var = 18;

    // declaring switch cases
    switch (var) {
    case 15:
        printf("You are a kid");
        break;
    case 18:
        printf("Eligible for vote");
        break;
    default:
        printf("Default Case is executed");
        break;
    }

    return 0;
}
