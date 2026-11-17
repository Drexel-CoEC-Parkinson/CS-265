/* heap.c -- an array whose size is chosen at run time */
#include <stdio.h>
#include <stdlib.h>

int *make_squares(int n)
{
    int *result = malloc(n * sizeof(int));

    if (result == NULL)
        return NULL;
    for (int i = 0; i < n; i++)
        result[i] = i * i;
    return result;
}

int main(int argc, char *argv[])
{
    int n;

    if (argc != 2 || sscanf(argv[1], "%d", &n) != 1 || n < 1) {
        printf("Usage: heap N   (N is 1 or more)\n");
        return 1;
    }

    int *squares = make_squares(n);
    if (squares == NULL) {
        printf("Out of memory\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        printf("%d ", squares[i]);
    printf("\n");

    free(squares);
    return 0;
}
