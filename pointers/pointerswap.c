#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    int x = 1, y = 2;

    swap(&x, &y);
    printf("x is %d, y is %d\n", x, y);    /* x is 2, y is 1 */
    return 0;
}
