#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int cap = 2, n = 0, x;
    int *a = malloc(cap * sizeof(*a));

    if (a == NULL)
        return 1;

    while (scanf("%d", &x) == 1) {
        if (n == cap) {                       /* full: double it */
            int *tmp = realloc(a, 2 * cap * sizeof(*a));
            if (tmp == NULL) {
                free(a);
                return 1;
            }
            a = tmp;
            cap *= 2;
            printf("(grew to %d)\n", cap);
        }
        a[n++] = x;
    }

    printf("read %d numbers\n", n);
    free(a);
    return 0;
}
