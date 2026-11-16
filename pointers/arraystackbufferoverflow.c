#include <stdio.h>
#define N 5

int main(void)
{
    int a[N];
    int i, sum = 0;

    for (i = 0; i <= N; i++)     /* BUG: should be i < N */
        a[i] = i;

    for (i = 0; i < N; i++)
        sum += a[i];
    printf("sum is %d\n", sum);
    return 0;
}
