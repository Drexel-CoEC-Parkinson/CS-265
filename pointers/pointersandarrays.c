#include <stdio.h>
#define N 5

int main(void)
{
    int a[N] = {10, 20, 30, 40, 50};
    int i, *p;

    for (i = 0; i < N; i++)          /* Option 1: subscripts */
        printf("%d ", a[i]);
    printf("\n");

    for (p = a; p < a + N; p++)      /* Option 2: pointers */
        printf("%d ", *p);
    printf("\n");
    return 0;
}
