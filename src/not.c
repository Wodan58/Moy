/*
    module  : not.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
not  :  X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
PRIVATE void do_not(void)
{
    int num = 0;

#ifndef NCHECK
    unsigned op, op1;

    if (optimizing) {
	op = top_history(&op1);
	chg_history(op == SET_ ? SET_ : BOOLEAN_);
    }
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM("not");
#endif
    switch (stk->op) {
    case SET_:
	if (OUTSIDE)
	    stk->u.set = ~stk->u.set;
	else
	    UNARY(SET_NEWNODE, ~stk->u.set);
	return;
    case STRING_:
	num = *stk->u.str != 0;
	break;
    case LIST_:
	num = !stk->u.lis;
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	num = !stk->u.num;
	break;
    case FLOAT_:
	num = !stk->u.dbl;
	break;
    case FILE_:
	num = !stk->u.fil;
	break;
#ifndef NCHECK
    default:
	BADDATA("not");
#endif
    }
    if (OUTSIDE) {
	stk->u.num = num;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, num);
}
