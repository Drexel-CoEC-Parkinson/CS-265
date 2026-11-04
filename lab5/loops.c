/* loops.c -- trace each loop.  Run:  ./loops N   (N is 1 to 4) */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s N\n", argv[0]);
        return 1;
    }

    int which = atoi(argv[1]);
    int i;

    if (which == 1) {
        for (i = 0; i < 7; i += 2)
            printf("%d ", i);
        printf("\n");
    } else if (which == 2) {
        i = 3;
        do {
            printf("%d ", i);
            i++;
        } while (i < 3);
        printf("\n");
    } else if (which == 3) {
        for (i = 0; i < 4; i++);
            printf("%d ", i);
        printf("\n");
    } else if (which == 4) {
        i = 10;
        while (i > 0) {
            printf("%d\n", i);
            i /= 2;
            i++;
        }
    }

    return 0;
}
