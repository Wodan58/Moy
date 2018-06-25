/*
    module  : over.c
    version : 1.1
    date    : 06/25/18
*/
#include "runtime.h"

/**
over  :  X Y  ->  X Y X
Pushes an extra copy of the second item X on top of the stack.
*/
PRIVATE void do_over(void)
{
#ifndef NCHECK
    unsigned op, op1;

    if (optimizing) {
	op = sub_history(&op1);
	add_history2(op, op1);
    }
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    TWOPARAMS("over");
#endif
    DUPLICATE(stk->next);
}
