/* exprs.c -- what does each expression evaluate to? */
#include <stdio.h>

int main(void)
{
    int i = 2, j = 1, k = 0;

    printf("1: %d\n", i > j);
    printf("2: %d\n", i > j && k);
    printf("3: %d\n", i > j || k);
    printf("4: %d\n", !k);
    printf("5: %d\n", !j < i);
    printf("6: %d\n", i & j);
    printf("7: %d\n", i && j);
    printf("8: %d\n", 3 > 2 > 1);
    printf("9: %d\n", k != 0 && j / k > 1);

    return 0;
}
