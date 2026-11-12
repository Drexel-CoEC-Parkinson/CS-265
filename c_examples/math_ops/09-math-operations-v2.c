// math_operations.c
#include "09-math_operations.h"
#include <stdio.h>

int add(int a, int b) {
    if(a < 0 || b < 0){
        return 0;
    }
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

float divide(int a, int b) {
    if (b != 0) {
        return (float)a / b;
    } else {
        printf("Error: Division by zero!\n");
        return 0.0;
    }
}
