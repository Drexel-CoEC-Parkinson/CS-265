/* divide.c -- one function, two results */
#include <stdio.h>

void divide(int a, int b, int *quot, int *rem)
{
    *quot = a / b;
    *rem = a % b;
}

int main(void)
{
    int q, r;

    divide(17, 5, &q, &r);
    printf("17 / 5:  quotient %d, remainder %d\n", q, r);

    divide(-17, 5, &q, &r);
    printf("-17 / 5: quotient %d, remainder %d\n", q, r);

    return 0;
}
