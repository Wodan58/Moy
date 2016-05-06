/*
    module  : null.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
null  :  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
/* null.c */
PRIVATE void null_(void)
{
    int num = 0;

    ONEPARAM("null");
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
    default:
	BADDATA("null");
    }
    if (OUTSIDE) {
	stk->u.num = num;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, num);
}
