/*
    module  : exp.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
exp  :  F  ->  G
G is e (2.718281828...) raised to the Fth power.
*/
#define PROCEDURE	do_exp
#define NAME		"exp"
#define FUNC		exp
#include "ufloat.c"
