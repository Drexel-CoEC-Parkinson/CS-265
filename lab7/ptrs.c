/* ptrs.c -- pointers, arrays, and one declaration trap */
#include <stdio.h>

int main(void)
{
    int a[5] = {3, 1, 4, 1, 5};
    int *p = a, q = 9;

    printf("A: %d\n", *p + 1);
    printf("B: %d\n", *(p + 1));
    printf("C: %zu\n", sizeof p);
    printf("D: %zu\n", sizeof q);

    p = &a[4];
    printf("E: %d\n", *p);
    printf("F: %td\n", p - a);

    p -= 2;
    printf("G: %d\n", p[1]);
    printf("H: %d\n", *p * *(p + 1));

    return 0;
}
