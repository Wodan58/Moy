/*
    module  : pop.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
pop  :  X  ->
Removes X from top of the stack.
*/
PRIVATE void do_pop(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM("pop");
#endif
    POP(stk);
}
