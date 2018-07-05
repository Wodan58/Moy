/*
    module  : first.c
    version : 1.8
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_first(void)
{
    code_t *cur;

    TRACE;
    cur = (code_t *)stk[-1];
    stk[-1] = cur->num;
}
#else
/**
first  :  A  ->  F
F is the first member of the non-empty aggregate A.
*/
PRIVATE void do_first(void)
{
    int i = 0;

#ifndef NCHECK
    if (compiling && AGGREGATE_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("first");
    switch (stk->op) {
    case LIST_:
	CHECKEMPTYLIST(stk->u.lis, "first");
	if (OUTSIDE) {
	    stk->op = stk->u.lis->op;
	    stk->u = stk->u.lis->u;
	} else
	    GUNARY(stk->u.lis->op, stk->u.lis->u.ptr);
	break;
    case STRING_:
	CHECKEMPTYSTRING(stk->u.str, "first");
	if (OUTSIDE) {
	    stk->u.num = *stk->u.str;
	    stk->op = CHAR_;
	} else
	    UNARY(CHAR_NEWNODE, *stk->u.str);
	break;
    case SET_:
	CHECKEMPTYSET(stk->u.set, "first");
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
#endif
