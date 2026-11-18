#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int n = 10;
    char *p = malloc(n + 1);

    if (p == NULL)
        return 1;

    strcpy(p, "abc");
    for (int i = 0; i < 4; i++)
        printf("p[%d] is %3d\n", i, p[i]);   /* 97 98 99 0 */
    printf("string: %s\n", p);
    free(p);
    return 0;
}
