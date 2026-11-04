/* readint.c -- add up integers until end of input, the safe way:
 * read a whole line with fgets, then parse it with sscanf. */
#include <stdio.h>

#define LINE_MAX_LEN 100

int main(void)
{
    char line[LINE_MAX_LEN];
    int x, sum = 0;

    while (fgets(line, LINE_MAX_LEN, stdin) != NULL) {
        if (sscanf(line, "%d", &x) != 1) {
            printf("skipping: %s", line);
            continue;
        }
        sum += x;
        printf("sum so far: %d\n", sum);
    }
    return 0;
}
