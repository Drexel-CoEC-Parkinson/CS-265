/* specs.c -- printf format specifiers */
#include <stdio.h>

int main(void)
{
    int  n = 255;
    char c = 'A';
    double x = 1.5;

    printf("1: %d\n", n);
    printf("2: %x\n", n);
    printf("3: %o\n", n);
    printf("4: %c\n", c);
    printf("5: %d\n", c);
    printf("6: %f\n", x);
    printf("7: %e\n", x);
    printf("8: %g\n", x);
    printf("9: 100%%\n");
    return 0;
}
