/* byvalue.c -- what can a function change? */
#include <stdio.h>

void swap(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
    printf("inside swap: a=%d b=%d\n", a, b);
}

void reset(int n)
{
    n = 0;
}

int main(void)
{
    int x = 3, y = 7;

    swap(x, y);
    printf("after swap:  x=%d y=%d\n", x, y);

    reset(x);
    printf("after reset: x=%d\n", x);

    return 0;
}
