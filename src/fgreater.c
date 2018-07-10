/*
    module  : fgreater.c
    version : 1.2
    date    : 07/10/18
*/
#ifndef FGREATER_X
#define FGREATER_C

#ifdef RUNTIME
void do_fgreater(void)
{
    float dbl1, dbl2;

    TRACE;
    memcpy(&dbl1, &stk[-2], sizeof(float));
    memcpy(&dbl2, &stk[-1], sizeof(float));
    stk[-2] = dbl1 > dbl2;
    (void)do_pop();
}
#else
/**
.>  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than Y.  Also supports float.
*/
#define PROCEDURE	do_fgreater
#define NAME		">"
#define CONSTRUCTOR	BOOLEAN_
#define OPR		>
#define SETCMP		i!=j&&!(j&~i)
#include "comprel.h"
#endif
#endif
