/* swap.c -- a swap that actually works */
#include <stdio.h>

void swap(int *a, int *b)
{
    /* TODO: write the body (three lines) */
}

int main(void)
{
    int x = 3, y = 7;

    swap(&x, &y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}
