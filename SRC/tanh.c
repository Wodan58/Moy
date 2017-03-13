/*
    module  : tanh.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
tanh  :  F  ->  G
G is the hyperbolic tangent of F.
*/
#define PROCEDURE	do_tanh
#define NAME		"tanh"
#define FUNC		tanh
#include "ufloat.c"
