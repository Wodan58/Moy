/*
    module  : get.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
get  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
PRIVATE void do_get(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    readfactor(yylex());
}
