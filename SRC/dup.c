/*
    module  : dup.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
dup  :  X  ->  X X
Pushes an extra copy of X onto stack.
*/
PRIVATE void do_dup(void)
{
#ifndef NCHECK
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM("dup");
#endif
    DUPLICATE(stk);
}
