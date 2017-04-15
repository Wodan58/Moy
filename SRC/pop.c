/*
    module  : pop.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
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
