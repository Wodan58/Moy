/*
    module  : rest.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef REST_X
#define REST_C

#ifdef NEW_RUNTIME
void do_rest(void)
{
    code_t *cur;

    TRACE;
    cur = (code_t *)stk[-1];
    stk[-1] = (node_t)cur->next;
}
#else
/**
rest  :  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
PRIVATE void do_rest(void)
{
    int i = 0;
    char *str;

#ifndef OLD_RUNTIME
    if (compiling && AGGREGATE_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("rest");
    switch (stk->op) {
    case LIST_:
	CHECKEMPTYLIST(stk->u.lis, "rest");
	if (OUTSIDE)
	    stk->u.lis = stk->u.lis->next;
	else
	    UNARY(LIST_NEWNODE, stk->u.lis->next);
	break;
    case STRING_:
	str = stk->u.str;
	CHECKEMPTYSTRING(str, "rest");
	if (OUTSIDE)
	    stk->u.str = ++str;
	else
	    UNARY(STRING_NEWNODE, ++str);
	break;
    case SET_:
	CHECKEMPTYSET(stk->u.set, "rest");
	while (!(stk->u.set & (1 << i)))
	    i++;
	if (OUTSIDE)
	    stk->u.set = stk->u.set & ~(1 << i);
	else
	    UNARY(SET_NEWNODE, stk->u.set & ~(1 << i));
	break;
    default:
	BADAGGREGATE("rest");
	break;
    }
}
#endif
#endif
