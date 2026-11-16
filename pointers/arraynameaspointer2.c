#include <stdio.h>
#define N 6

int main(void)
{
    int a[N] = {4, 8, 15, 16, 23, 42};
    int sum = 0, *p;

    for (p = a; p < a + N; p++)
        sum += *p;
    printf("sum is %d\n", sum);     /* 108 */
    return 0;
}
