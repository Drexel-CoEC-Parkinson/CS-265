/* fmt.c -- printf width, precision, and flags.  The bars show the edges. */
#include <stdio.h>

int main(void)
{
    printf("A: |%5d|\n", 42);
    printf("B: |%-5d|\n", 42);
    printf("C: |%05d|\n", 42);
    printf("D: |%x|%o|\n", 255, 255);
    printf("E: |%8.3f|\n", 3.14159);
    printf("F: |%-8.1f|\n", 3.14159);
    printf("G: |%e|\n", 1500.0);
    printf("H: |%g|\n", 1500.0);
    printf("I: |%10s|\n", "tux");
    printf("J: |%-10s|\n", "tux");
    printf("K: |%.2s|\n", "tux");
    printf("L: |%3d|\n", 123456);
    printf("M: 100%%\n");

    return 0;
}
