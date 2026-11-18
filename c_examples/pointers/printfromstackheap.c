#include <stdio.h>
#include <stdlib.h>

int g_init = 100;       /* data  */
int g_uninit;           /* BSS   */

int main(void)
{
    int local = 5;                      /* stack */
    int *h = malloc(sizeof(int));       /* heap  */

    printf("text  (main)     %p\n", (void *) main);
    printf("data  (g_init)   %p\n", (void *) &g_init);
    printf("BSS   (g_uninit) %p\n", (void *) &g_uninit);
    printf("heap  (*h)       %p\n", (void *) h);
    printf("stack (local)    %p\n", (void *) &local);

    free(h);
    return 0;
}
