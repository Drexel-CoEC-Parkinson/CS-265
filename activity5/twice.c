/* twice.c -- what can a function change? */
#include <stdio.h>

int twice(int x)
{
    x = x * 2;
    return x + 1;
}

int main(void)
{
    int a = 5;
    int b = twice(a);

    printf("a = %d, b = %d\n", a, b);
    return 0;
}
