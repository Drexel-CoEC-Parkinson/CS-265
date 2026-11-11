/* arrays.c -- declaring, initializing, and measuring arrays */
#include <stdio.h>

#define N 5

int main(void)
{
    int a[N] = {4, 8, 15};
    int b[] = {1, 2, 3, 4, 5, 6, 7};
    int c[N];

    printf("A:");
    for (int i = 0; i < N; i++)
        printf(" %d", a[i]);
    printf("\n");

    printf("B: %zu\n", sizeof a);
    printf("C: %zu\n", sizeof b / sizeof b[0]);

    for (int i = 0; i < N; i++)
        c[i] = i * i;
    printf("D: %d\n", c[N - 1]);

    int total = 0;
    for (int i = 0; i < N; i++)
        total += a[i];
    printf("E: %d\n", total);

    return 0;
}
