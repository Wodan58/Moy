/*
    module  : pop.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
pop  :  X  ->
Removes X from top of the stack.
*/
PRIVATE void do_pop(void)
{
#ifndef NCHECK
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM("pop");
#endif
    POP(stk);
}
