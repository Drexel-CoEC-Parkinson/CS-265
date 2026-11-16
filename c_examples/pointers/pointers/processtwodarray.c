#include <stdio.h>
#define ROWS 3
#define COLS 4

int main(void)
{
    int m[ROWS][COLS];
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            m[i][j] = i * 10 + j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++)
            printf("%3d ", m[i][j]);
        printf("\n");
    }
    return 0;
}
