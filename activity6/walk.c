/* walk.c -- pointers and arrays */
#include <stdio.h>

int main(void)
{
    int a[4] = {10, 20, 30, 40};
    int *p = a;

    printf("A: %d\n", *p);
    printf("B: %d\n", *(p + 2));
    printf("C: %d\n", p[1]);

    p++;
    printf("D: %d\n", *p);
    printf("E: %d\n", (int) (&a[3] - p));

    printf("F: %p\n", (void *) &a[0]);
    printf("G: %p\n", (void *) &a[1]);

    return 0;
}
