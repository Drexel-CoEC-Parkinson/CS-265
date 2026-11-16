#include <stdio.h>

int main(void)
{
    int a[10], *p, *q, i;

    for (i = 0; i < 10; i++)
        a[i] = i * 100;

    p = &a[2];
    printf("*p is %d\n", *p);               /* 200 */
    q = p + 3;
    printf("*q is %d\n", *q);               /* 500 */
    p += 6;
    printf("*p is %d\n", *p);               /* 800 */
    printf("p is at index %td\n", p - a);   /* 8   */
    return 0;
}
