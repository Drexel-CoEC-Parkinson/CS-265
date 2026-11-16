#include <stdio.h>

int main(void)
{
    int a[10] = {0}, *p;

    p = &a[0];
    *p = 5;
    printf("a[0] is %d\n", a[0]);   /* 5 */

    p = &a[3];
    *p = 7;
    printf("a[3] is %d\n", a[3]);   /* 7 */
    return 0;
}
