/*
    module  : small.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
small  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
PRIVATE void do_small(void)
{
    int small = 0;

#ifndef NCHECK
    if (optimizing)
	chg_history(BOOLEAN_);
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM("small");
#endif
    switch (stk->op) {
    case BOOLEAN_:
    case INTEGER_:
	small = stk->u.num < 2;
	break;
    case SET_:
	if (!stk->u.set)
	    small = 1;
	else {
	    int i = 0;
	    while (!(stk->u.set & (1 << i)))
		i++;
	    small = (stk->u.set & ~(1 << i)) == 0;
	}
	break;
    case STRING_:
	small = !stk->u.str || !*stk->u.str || !stk->u.str[1];
	break;
    case LIST_:
	small = !stk->u.lis || !stk->u.lis->next;
	break;
#ifndef NCHECK
    default:
	BADDATA("small");
#endif
    }
    if (OUTSIDE) {
	stk->u.num = small;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, small);
}
