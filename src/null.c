/*
    module  : null.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef NULL_X
#define NULL_C

#ifdef RUNTIME
void do_null(void)
{
    TRACE;
    if (stk[-1] > start_of_data && stk[-1] < start_of_heap)
	stk[-1] = !stk[-1] || !strlen((char *)stk[-1]);
    else
	stk[-1] = !stk[-1];
}
#else
/**
null  :  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
PRIVATE void do_null(void)
{
    int num = 0;

#ifndef NCHECK
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
#endif
#endif
