/* sign.c -- returns 1, -1, or ... ? */
#include <stdio.h>

int sign(int n)
{
    if (n > 0)
        return 1;
    else if (n < 0)
        return -1;
}

int main(void)
{
    printf("sign(7)  = %d\n", sign(7));
    printf("sign(-4) = %d\n", sign(-4));
    printf("sign(0)  = %d\n", sign(0));
    return 0;
}
