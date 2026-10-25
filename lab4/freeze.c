/* freeze.c -- what does the compiler actually see? */
#include <stdio.h>

#define FREEZING_PT 32.0f
#define BOILING_PT  212.0f
#define SHOW_EXTRA  0

int main(void)
{
    printf("Water freezes at %f F\n", FREEZING_PT);

#if 0
    /* Old version -- kept for reference */
    printf("Water boils at %f F\n", BOILING_PT);   /* TODO: Celsius? */
#endif

#if SHOW_EXTRA
    printf("Range: %f degrees\n", BOILING_PT - FREEZING_PT);
#endif

    return 0;
}
