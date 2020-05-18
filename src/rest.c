/*
    module  : rest.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef REST_C
#define REST_C

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
	stk->u.lis = stk->u.lis->next;
	break;
    case STRING_:
	str = stk->u.str;
	CHECKEMPTYSTRING(str, "rest");
	stk->u.str = ++str;
	break;
    case SET_:
	CHECKEMPTYSET(stk->u.set, "rest");
	while (!(stk->u.set & ((long_t)1 << i)))
	    i++;
	stk->u.set = stk->u.set & ~((long_t)1 << i);
	break;
    default:
	BADAGGREGATE("rest");
	break;
    }
}
#endif
