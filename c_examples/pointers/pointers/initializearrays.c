#include <stdio.h>

void show(const char *label, int a[], int n)
{
    printf("%-10s", label);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main(void)
{
    int full[5]  = {1, 2, 3, 4, 5};
    int part[5]  = {1, 2};
    int zeros[5] = {0};
    int ones[5]  = {1};
    int none[5];

    show("full:", full, 5);
    show("part:", part, 5);
    show("zeros:", zeros, 5);
    show("ones:", ones, 5);
    show("none:", none, 5);     /* garbage; gcc may warn */
    return 0;
}
