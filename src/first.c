/*
    module  : first.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef FIRST_C
#define FIRST_C

/**
first  :  A  ->  F
F is the first member of the non-empty aggregate A.
*/
PRIVATE void do_first(void)
{
    int i = 0;

#ifndef OLD_RUNTIME
    if (compiling && AGGREGATE_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("first");
    switch (stk->op) {
    case LIST_:
	CHECKEMPTYLIST(stk->u.lis, "first");
	stk->op = stk->u.lis->op;
	stk->u = stk->u.lis->u;
	break;
    case STRING_:
	CHECKEMPTYSTRING(stk->u.str, "first");
	stk->u.num = *stk->u.str;
	stk->op = CHAR_;
	break;
    case SET_:
	CHECKEMPTYSET(stk->u.set, "first");
	while (!(stk->u.set & ((long_t)1 << i)))
	    i++;
	stk->u.num = i;
	stk->op = INTEGER_;
	break;
    default:
	BADAGGREGATE("first");
	break;
    }
}
#endif
