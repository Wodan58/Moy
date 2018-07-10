/*
    module  : round.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef ROUND_X
#define ROUND_C

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
#endif
