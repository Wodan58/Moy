/*
    module  : fremove.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
fremove  :  P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
PRIVATE void do_fremove(void)
{
#ifndef NCHECK
    if (optimizing)
	chg_history(BOOLEAN_);
    COMPILE;
    ONEPARAM("fremove");
    STRING("fremove");
#endif
    if (OUTSIDE) {
	stk->next->u.num = !remove(stk->u.str);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	UNARY(BOOLEAN_NEWNODE, !remove(stk->u.str));
}
