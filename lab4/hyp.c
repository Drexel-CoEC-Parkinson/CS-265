/* hyp.c -- needs the math library */
#include <stdio.h>
#include <math.h>

double hyp(double a, double b)
{
    return sqrt(a * a + b * b);
}

int main(void)
{
    printf("hyp(3, 4) = %g\n", hyp(3.0, 4.0));
    return 0;
}
