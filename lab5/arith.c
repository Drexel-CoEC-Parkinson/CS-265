/* arith.c -- integers and floats follow different rules */
#include <stdio.h>

int main(void)
{
    int a = 9, t = 2;
    int total = 17, n = 5;

    printf("A: %d\n", 1 / 2 * a * t * t);
    printf("B: %d\n", a * t * t / 2);
    printf("C: %d\n", total / n);
    printf("D: %d\n", total % n);
    printf("E: %.1f\n", 7 / 2 + 0.5);
    printf("F: %.2f\n", (double) total / n);
    printf("G: %.2f\n", (double) (total / n));

    printf("H: %d\n", 0.1 + 0.2 == 0.3);
    printf("I: %.17f\n", 0.1 + 0.2);

    float big = 16777217.0;
    printf("J: %.1f\n", big);

    double average = total / n;      /* BUG: fix this line in Q2 */
    printf("average: %.2f\n", average);

    return 0;
}
