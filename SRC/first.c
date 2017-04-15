/*
    module  : first.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
first  :  A  ->  F
F is the first member of the non-empty aggregate A.
*/
PRIVATE void do_first(void)
{
    int i = 0;

#ifndef NCHECK
    unsigned op, op1;

    if (optimizing)
	op = pop_history(&op1);
    if (optimizing && AGGREGATE(stk))
	;
    else
	COMPILE;
    ONEPARAM("first");
#endif
    switch (stk->op) {
    case LIST_:
#ifndef NCHECK
	if (optimizing)
	    add_history(op1);
	CHECKEMPTYLIST(stk->u.lis, "first");
#endif
	if (OUTSIDE) {
	    stk->op = stk->u.lis->op;
	    stk->u = stk->u.lis->u;
	} else
	    GUNARY(stk->u.lis->op, stk->u.lis->u.ptr);
	break;
    case STRING_:
#ifndef NCHECK
	if (optimizing)
	    add_history(CHAR_);
	CHECKEMPTYSTRING(stk->u.str, "first");
#endif
	if (OUTSIDE) {
	    stk->u.num = *stk->u.str;
	    stk->op = CHAR_;
	} else
	    UNARY(CHAR_NEWNODE, *stk->u.str);
	break;
    case SET_:
#ifndef NCHECK
	if (optimizing)
	    add_history(INTEGER_);
	CHECKEMPTYSET(stk->u.set, "first");
#endif
	while (!(stk->u.set & (1 << i)))
	    i++;
	if (OUTSIDE) {
	    stk->u.num = i;
	    stk->op = INTEGER_;
	} else
	    UNARY(INTEGER_NEWNODE, i);
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("first");
#endif
    }
}
