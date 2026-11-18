#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *p = malloc(100);

    if (p == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
    strcpy(p, "stored on the heap");
    printf("%s (block starts at %p)\n", p, (void *) p);
    free(p);
    return 0;
}
