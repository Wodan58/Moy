/*
    module  : round.c
    version : 1.5
    date    : 07/02/18
*/

PRIVATE double round2(double num)
{
    if (num < 0)
	return -floor(-num + 0.5);
    return floor(num + 0.5);
}

/**
round  :  F  ->  G
G is F rounded to the nearest integer.
*/
#define PROCEDURE	do_round
#define NAME		"round"
#define FUNC		round2
#include "ufloat.h"
/* round.c */
