/*
    module  : get.c
    version : 1.5
    date    : 04/15/17
*/
#include "runtime.h"

/*
get  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
PRIVATE void do_get(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    readfactor(yylex());
}
