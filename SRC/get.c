/*
    module  : get.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
get  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
/* get.c */
PRIVATE void get_(void)
{
    getsym();
    readfactor();
}
