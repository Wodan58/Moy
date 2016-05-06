/*
    module  : choice.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
choice  :  B T F  ->  X
If B is true, then X = T else X = F.
*/
/* choice.c */
PRIVATE void choice_(void)
{
    THREEPARAMS("choice");
    if (OUTSIDE) {
	if (stk->next->next->u.num) {
	    stk->next->next->u = stk->next->u;
	    stk->next->next->op = stk->next->op;
	} else {
	    stk->next->next->u = stk->u;
	    stk->next->next->op = stk->op;
	}
	POP(stk);
	POP(stk);
    } else if (stk->next->next->u.num)
	stk = newnode(stk->next->op, stk->next->u.ptr, stk->next->next->next);
    else
	stk = newnode(stk->op, stk->u.ptr, stk->next->next->next);
}
