#include <stdio.h>
#define N 5

int main(void)
{
    int a[N], sum = 0, *p;

    printf("Enter %d integers: ", N);
    for (p = a; p < a + N; p++)
        scanf("%d", p);

    for (p = a; p < a + N; p++)
        sum += *p;
    printf("sum is %d\n", sum);
    return 0;
}
