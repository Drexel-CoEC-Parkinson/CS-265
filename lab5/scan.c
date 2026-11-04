/* scan.c -- what does scanf return? */
#include <stdio.h>

int main(void)
{
    int a = -1, b = -1;
    int n = scanf("%d %d", &a, &b);

    printf("n=%d a=%d b=%d\n", n, a, b);
    return 0;
}
