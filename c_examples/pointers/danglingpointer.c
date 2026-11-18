#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *p = malloc(4);

    if (p == NULL)
        return 1;
    strcpy(p, "abc");
    free(p);

    strcpy(p, "xyz");       /*** WRONG: p is dangling ***/
    printf("%s\n", p);
    return 0;
}
