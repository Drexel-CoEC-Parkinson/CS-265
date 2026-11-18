#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, i, *a;

    printf("How many numbers? ");
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;

    a = malloc(n * sizeof(*a));
    if (a == NULL) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        a[i] = i * i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    free(a);
    return 0;
}
