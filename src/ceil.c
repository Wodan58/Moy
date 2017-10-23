/*
    module  : ceil.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
ceil  :  F  ->  G
G is the float ceiling of F.
*/
#define PROCEDURE	do_ceil
#define NAME		"ceil"
#define FUNC		ceil
#include "ufloat.c"
