#include <stdio.h>

void doubleAll(int a[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] *= 2;                  /* changes the caller's array */
}

int count(const char *s)            /* no length needed: sentinel */
{
    int n = 0;

    while (s[n] != '\0')
        n++;
    return n;
}

int main(void)
{
    int nums[4] = {1, 2, 3, 4};

    doubleAll(nums, 4);
    for (int i = 0; i < 4; i++)
        printf("%d ", nums[i]);     /* 2 4 6 8 */
    printf("\n%d\n", count("bash"));   /* 4 */
    return 0;
}
