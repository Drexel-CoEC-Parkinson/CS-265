/* fmtbad.c -- the format string and the arguments disagree */
#include <stdio.h>

int main(void)
{
    printf("%d\n", 3.5);
    printf("%f\n", 7);
    printf("%d %d\n", 1);

    return 0;
}
