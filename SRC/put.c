/*
    module  : put.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
put  :  X  ->
Writes X to output, pops X off stack.
*/
/* put.c */
USETOP(put_, "put", ONEPARAM, writefactor(stk, stdout); printf(" "))
