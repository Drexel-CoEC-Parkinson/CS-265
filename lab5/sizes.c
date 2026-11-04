/* sizes.c -- how big is each type on this machine? */
#include <stdio.h>

int main(void)
{
    printf("char        %zu\n", sizeof(char));
    printf("short       %zu\n", sizeof(short));
    printf("int         %zu\n", sizeof(int));
    printf("long        %zu\n", sizeof(long));
    printf("float       %zu\n", sizeof(float));
    printf("double      %zu\n", sizeof(double));
    printf("long double %zu\n", sizeof(long double));

    short s = 32767;
    s = s + 1;
    printf("short past its max: %d\n", s);

    unsigned int u = 0;
    u = u - 1;
    printf("unsigned below 0:   %u\n", u);

    return 0;
}
