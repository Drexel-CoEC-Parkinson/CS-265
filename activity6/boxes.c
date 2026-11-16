/* boxes.c -- draw the memory, then check it with gdb */
#include <stdio.h>

int main(void)
{
    int x = 10;
    int y = 3;
    int *p = &x;

    *p = 25;
    y = *p + 1;
    p = &y;
    *p = *p * 2;

    printf("x = %d, y = %d\n", x, y);
    return 0;
}
