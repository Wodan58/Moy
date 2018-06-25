/*
    module  : put.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
put  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("put");
#endif
    writefactor(stk, stdout);
    putchar(' ');
    POP(stk);
}
