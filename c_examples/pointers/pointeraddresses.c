#include <stdio.h>

int main(void)
{
    int    ia[3];
    double da[3];
    char   ca[3];
    int    *ip = ia;
    double *dp = da;
    char   *cp = ca;

    printf("int:    %p then %p\n", (void *) ip, (void *) (ip + 1));
    printf("double: %p then %p\n", (void *) dp, (void *) (dp + 1));
    printf("char:   %p then %p\n", (void *) cp, (void *) (cp + 1));
    return 0;
}
