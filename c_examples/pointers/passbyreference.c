#include <stdio.h>
#define MAX 5

int main(void)
{
    int a[MAX];
    int i;

    for (i = 0; i < MAX; i++)
        a[i] = i * i;

    for (i = 0; i < MAX; i++)
        printf("a[%d] is %d\n", i, a[i]);
    return 0;
}
