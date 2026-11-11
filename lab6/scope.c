/* scope.c -- which variable is which? */
#include <stdio.h>

int count = 100;                /* a global variable */

void bump(void)
{
    static int calls = 0;       /* static: keeps its value between calls */
    int local = 0;

    calls++;
    local++;
    count++;
    printf("bump: calls=%d local=%d count=%d\n", calls, local, count);
}

int main(void)
{
    bump();
    bump();

    int count = 5;              /* a local variable with the same name */
    printf("main: count=%d\n", count);
    bump();

    for (int i = 0; i < 2; i++) {
        int count = i * 10;
        printf("loop: count=%d\n", count);
    }
    printf("main: count=%d\n", count);

    return 0;
}
