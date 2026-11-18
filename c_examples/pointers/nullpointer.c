#include <stdio.h>

int main(void)
{
    int x = 5;
    int *p = NULL;

    if (!p)
        printf("p is NULL\n");

    p = &x;
    if (p)
        printf("p points to %d\n", *p);
    return 0;
}
