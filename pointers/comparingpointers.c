#include <stdio.h>

int main(void)
{
    int a[10], *p, *q;

    p = &a[5];
    q = &a[1];
    printf("p <= q is %d\n", p <= q);   /* 0 */
    printf("p >= q is %d\n", p >= q);   /* 1 */
    printf("p == q is %d\n", p == q);   /* 0 */

    q += 4;                             /* q now points to a[5] too */
    printf("p == q is %d\n", p == q);   /* 1 */
    return 0;
}
