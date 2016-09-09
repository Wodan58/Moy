/*
    module  : get.c
    version : 1.3
    date    : 09/09/16
*/
#include "interp.h"

/*
get  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
/* get.c */
PRIVATE void get_(void)
{
    sym = yylex();
    readfactor();
}
