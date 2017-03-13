/*
    module  : cosh.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
cosh  :  F  ->  G
G is the hyperbolic cosine of F.
*/
#define PROCEDURE	do_cosh
#define NAME		"cosh"
#define FUNC		cosh
#include "ufloat.c"
