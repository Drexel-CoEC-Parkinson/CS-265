/* switch.c -- a switch statement, and what break does */
#include <stdio.h>

void describe(int n)
{
    printf("%d: ", n);
    switch (n) {
    case 1:
        printf("one ");
    case 2:
        printf("two ");
        break;
    case 3:
    case 4:
        printf("three-or-four ");
        break;
    default:
        printf("other ");
    }
    printf("\n");
}

int main(void)
{
    for (int n = 0; n <= 5; n++)
        describe(n);
    return 0;
}
