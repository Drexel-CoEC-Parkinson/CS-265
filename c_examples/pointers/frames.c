#include <stdio.h>

void f(int a, int b)
{
    int x;

    x = a + b;
    printf("x is %d\n", x);
}

int main(void)
{
    f(1, 2);
    printf("hello world\n");
    return 0;
}
