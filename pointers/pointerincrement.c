#include <stdio.h>

int main(void)
{
    int b[] = {10, 20, 30, 40};
    int *p, v;

    p = b; v = *p++;
    printf("*p++   : v is %d, p at b[%td], b[0] is %d\n", v, p - b, b[0]);

    p = b; v = (*p)++;
    printf("(*p)++ : v is %d, p at b[%td], b[0] is %d\n", v, p - b, b[0]);

    b[0] = 10;
    p = b; v = *++p;
    printf("*++p   : v is %d, p at b[%td], b[0] is %d\n", v, p - b, b[0]);

    p = b; v = ++*p;
    printf("++*p   : v is %d, p at b[%td], b[0] is %d\n", v, p - b, b[0]);
    return 0;
}
