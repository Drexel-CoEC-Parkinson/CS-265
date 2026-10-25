/* temp.c -- temperature conversions */
#include "temp.h"

double c_to_f(double c)
{
    return c * 9.0 / 5.0 + FREEZING_PT;
}
