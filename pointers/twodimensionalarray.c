#include <stdio.h>
#define ROWS 5
#define COLS 9

int main(void)
{
    int m[ROWS][COLS];

    printf("whole table: %zu bytes\n", sizeof(m));       /* 180 */
    printf("one row:     %zu bytes\n", sizeof(m[0]));    /* 36  */
    printf("one element: %zu bytes\n", sizeof(m[0][0])); /* 4   */
    return 0;
}
