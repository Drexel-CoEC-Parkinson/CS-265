/* vbugs.c -- three memory bugs.  It may even print the right thing. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const char *s = "valgrind";

    char *copy = malloc(strlen(s));
    strcpy(copy, s);
    printf("copy: %s\n", copy);
    free(copy);
    printf("first letter: %c\n", copy[0]);

    int *counts = malloc(3 * sizeof(int));
    counts[0] = 1;
    counts[1] = 2;
    if (counts[2] > 0)
        printf("third count is positive\n");
    free(counts);

    return 0;
}
