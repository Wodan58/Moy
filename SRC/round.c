/*
    module  : round.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
round  :  F  ->  G
G is F rounded to the nearest integer.
*/
/* round.c */
#define PROCEDURE	round_
#define NAME		"round"
#define FUNC		round
#include "ufloat.c"
