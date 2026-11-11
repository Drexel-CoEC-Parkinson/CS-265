/* bugs.c -- total and warmest of a week of (cold) temperatures.
 * The right answers are Total: -30 and Max: -1.  This prints neither. */
#include <stdio.h>

#define DAYS 7

int main(void)
{
    int temps[DAYS] = {-5, -2, -8, -1, -3, -7, -4};
    int total = 0, max = 0;

    for (int i = 0; i <= DAYS; i++) {
        total += temps[i];
        if (temps[i] > max)
            max = temps[i];
    }

    printf("Total: %d\n", total);
    printf("Max: %d\n", max);

    return 0;
}
