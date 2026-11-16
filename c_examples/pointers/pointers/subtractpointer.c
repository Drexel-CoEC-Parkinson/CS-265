#include <stdio.h>

int my_strlen(const char *s)
{
    const char *p = s;

    while (*p != '\0')
        p++;
    return p - s;       /* elements between start and terminator */
}

int main(void)
{
    printf("%d\n", my_strlen("hello"));   /* 5 */
    return 0;
}

