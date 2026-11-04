/* scanloop.c -- add up integers until end of input */
#include <stdio.h>

int main(void)
{
    int x, sum = 0;

    while (scanf("%d", &x) != EOF) {
        sum += x;
        printf("sum so far: %d\n", sum);
    }
    return 0;
}
