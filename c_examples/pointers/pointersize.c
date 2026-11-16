#include <stdio.h>

int main(void)
{
    int    *ip = NULL;
    double *dp = NULL;

    printf("size of an int pointer:    %zu bytes\n", sizeof(ip));
    printf("size of a double pointer:  %zu bytes\n", sizeof(dp));
    printf("value of ip:               %p\n", (void *) ip);
    return 0;
}
