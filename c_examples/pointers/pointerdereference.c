#include <stdio.h>

int main(void)
{
    int i = 42;
    int *p = &i;

    printf("before: i is %d, *p is %d\n", i, *p);
    *p = 5;
    printf("after:  i is %d, *p is %d\n", i, *p);

    int *bad = NULL;
    printf("about to dereference NULL...\n");
    *bad = 7;                 /* crashes here */
    return 0;
}
