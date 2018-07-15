/*
    module  : null_str.c
    version : 1.3
    date    : 07/15/18
*/
#ifndef NULL_STR_X
#define NULL_STR_C

#ifdef NEW_RUNTIME
void do_null_str(void)
{
    TRACE;
    stk[-1] = !stk[-1] || !strlen((char *)stk[-1]);
}
#else
/**
null_str  :  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
PRIVATE void do_null_str(void)
{
    int num = 0;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
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
	break;
    }
    if (OUTSIDE) {
	stk->u.num = num;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, num);
}
#endif
#endif
