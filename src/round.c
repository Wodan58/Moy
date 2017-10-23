/*
    module  : round.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

PRIVATE double round2(double num)
{
    if (num < 0)
	return -floor(-num + 0.5);
    return floor(num + 0.5);
}

/*
round  :  F  ->  G
G is F rounded to the nearest integer.
*/
#define PROCEDURE	do_round
#define NAME		"round"
#define FUNC		round2
#include "ufloat.c"
