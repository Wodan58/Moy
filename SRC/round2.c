/*
    module  : round2.c
    version : 1.1
    date    : 05/06/16
*/
#include <math.h>

double round(double num)
{
    if (num < 0)
	return -floor(-num + 0.5);
    return floor(num + 0.5);
}
