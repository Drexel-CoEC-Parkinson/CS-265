#include <stdio.h>
#define N 5

int main(void)
{
    int a[N] = {1, 2, 3, 4, 5};
    int sum = 0, *p;

    p = &a[0];
    while (p < &a[N])
        sum += *p++;
    printf("sum is %d\n", sum);     /* 15 */

    char src[] = "vim";
    char copy[10];
    char *s = src, *d = copy;

    while ((*d++ = *s++) != '\0')
        ;
    printf("copy is %s\n", copy);   /* vim */
    return 0;
}
