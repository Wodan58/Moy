/*
    module  : sinh.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
sinh  :  F  ->  G
G is the hyperbolic sine of F.
*/
#define PROCEDURE	do_sinh
#define NAME		"sinh"
#define FUNC		sinh
#include "ufloat.c"
