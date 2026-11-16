#include <stdio.h>

int main(void)
{
    int a[10] = {0};

    *a = 7;
    *(a + 1) = 12;
    printf("a[0] is %d, a[1] is %d\n", a[0], a[1]);     /* 7 and 12 */

    printf("a      is %p\n", (void *) a);
    printf("&a[0]  is %p\n", (void *) &a[0]);            /* same */
    printf("a + 2  is %p\n", (void *) (a + 2));
    printf("&a[2]  is %p\n", (void *) &a[2]);            /* same */
    printf("1[a]   is %d\n", 1[a]);                      /* 12 */
    return 0;
}
