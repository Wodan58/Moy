/*
    module  : not.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef NOT_C
#define NOT_C

/**
not  :  X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
PRIVATE void do_not(void)
{
    int num = 0;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("not");
    switch (stk->op) {
    case SET_:
	stk->u.set = ~stk->u.set;
	return;
    case BOOLEAN_:
	num = !stk->u.num;
	break;
    default:
	BADDATA("not");
	break;
    }
    stk->u.num = num;
    stk->op = BOOLEAN_;
}
#endif
