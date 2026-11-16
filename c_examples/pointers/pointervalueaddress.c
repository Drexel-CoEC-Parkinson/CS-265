#include <stdio.h>

int main(void)
{
    int i = 42;
    int *p = NULL;

    p = &i;
    printf("value of i:    %d\n", i);
    printf("address of i:  %p\n", (void *) &i);
    printf("value of p:    %p\n", (void *) p);
    printf("address of p:  %p\n", (void *) &p);
    return 0;
}
