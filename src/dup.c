/*
    module  : dup.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
dup  :  X  ->  X X
Pushes an extra copy of X onto stack.
*/
PRIVATE void do_dup(void)
{
#ifndef NCHECK
    unsigned op, op1;

    if (optimizing) {
	op = top_history(&op1);
	add_history2(op, op1);
    }
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM("dup");
#endif
    DUPLICATE(stk);
}
