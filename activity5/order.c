/* order.c -- a grading program with a bug */
#include <stdio.h>

int main(void)
{
    int score = 95;

    if (score >= 60)
        printf("D\n");
    else if (score >= 70)
        printf("C\n");
    else if (score >= 80)
        printf("B\n");
    else if (score >= 90)
        printf("A\n");
    else
        printf("F\n");

    return 0;
}
