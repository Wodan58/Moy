/*
    module  : null.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
null  :  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
PRIVATE void do_null(void)
{
    int num = 0;

#ifndef NCHECK
    if (optimizing)
	chg_history(BOOLEAN_);
    if (optimizing && VALID(stk))
	;
    else
	COMPILE;
    ONEPARAM("null");
#endif
    switch (stk->op) {
    case STRING_:
	num = !*stk->u.str;
	break;
    case FLOAT_:
	num = !stk->u.dbl;
	break;
    case FILE_:
	num = !stk->u.fil;
	break;
    case LIST_:
	num = !stk->u.lis;
	break;
    case SET_:
	num = !stk->u.set;
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	num = !stk->u.num;
	break;
#ifndef NCHECK
    default:
	BADDATA("null");
#endif
    }
    if (OUTSIDE) {
	stk->u.num = num;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, num);
}
