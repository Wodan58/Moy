/*
    module  : rest.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
rest  :  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
PRIVATE void do_rest(void)
{
    int i = 0;
    char *str;

#ifndef NCHECK
    if (optimizing && AGGREGATE(stk))
	;
    else
	COMPILE;
    ONEPARAM("rest");
#endif
    switch (stk->op) {
    case LIST_:
#ifndef NCHECK
	CHECKEMPTYLIST(stk->u.lis, "rest");
#endif
	if (OUTSIDE)
	    stk->u.lis = stk->u.lis->next;
	else
	    UNARY(LIST_NEWNODE, stk->u.lis->next);
	break;
    case STRING_:
	str = stk->u.str;
#ifndef NCHECK
	CHECKEMPTYSTRING(str, "rest");
#endif
	if (OUTSIDE)
	    stk->u.str = ++str;
	else
	    UNARY(STRING_NEWNODE, ++str);
	break;
    case SET_:
#ifndef NCHECK
	CHECKEMPTYSET(stk->u.set, "rest");
#endif
	while (!(stk->u.set & (1 << i)))
	    i++;
	if (OUTSIDE)
	    stk->u.set = stk->u.set & ~(1 << i);
	else
	    UNARY(SET_NEWNODE, stk->u.set & ~(1 << i));
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("rest");
#endif
    }
}
