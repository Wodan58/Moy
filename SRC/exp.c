/*
    module  : exp.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
exp  :  F  ->  G
G is e (2.718281828...) raised to the Fth power.
*/
/* exp.c */
#define PROCEDURE	exp_
#define NAME		"exp"
#define FUNC		exp
#include "ufloat.c"
