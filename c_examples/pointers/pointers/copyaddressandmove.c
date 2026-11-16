#include <stdio.h>

int main(void)
{
    int a[] = {5, 3, 9, 0, 2};
    int *p;

    p = a;
    while (*p != 0)
        p++;
    printf("first zero is at index %td\n", p - a);   /* 3 */
    return 0;
}
