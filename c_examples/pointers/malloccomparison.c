#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p;
    size_t n = 1000;

    if ((p = malloc(n * sizeof(int))) == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(EXIT_FAILURE);
    }
    printf("got room for %zu ints\n", n);
    free(p);
    return 0;
}
