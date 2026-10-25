/* status.c -- main's return value becomes the exit status */
#include <stdio.h>

int main(void)
{
    printf("Returning from main...\n");
    return 3;
}
