/*
    module  : not_set.c
    version : 1.2
    date    : 07/07/18
*/
#ifdef RUNTIME
void do_not_set(void)
{
    TRACE;
    stk[-1] = ~stk[-1];
}
#else
/**
not_set  :  X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
PRIVATE void do_not_set(void)
{
    int num = 0;

#ifndef NCHECK
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("not");
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
#endif
