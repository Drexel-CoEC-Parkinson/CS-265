#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = 5, i;
    int *m = malloc(n * sizeof(int));
    int *c = calloc(n, sizeof(int));

    if (m == NULL || c == NULL)
        return 1;

    printf("malloc: ");
    for (i = 0; i < n; i++)
        printf("%d ", m[i]);        /* garbage: may or may not be 0 */
    printf("\ncalloc: ");
    for (i = 0; i < n; i++)
        printf("%d ", c[i]);        /* always 0 */
    printf("\n");

    free(m);
    free(c);
    return 0;
}
