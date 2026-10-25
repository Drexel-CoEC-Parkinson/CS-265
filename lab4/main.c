/* main.c -- uses the functions in temp.c */
#include <stdio.h>
#include "temp.h"

int main(void)
{
    printf("100 C = %.1f F\n", c_to_f(100.0));
    printf("-40 C = %.1f F\n", c_to_f(-40.0));
    return 0;
}
