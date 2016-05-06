/*
    module  : rest.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
rest  :  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
/* rest.c */
PRIVATE void rest_(void)
{
    ONEPARAM("rest");
    switch (stk->op) {
    case SET_:
	 {
	    int i = 0;
	    CHECKEMPTYSET(stk->u.set, "rest");
	    while (!(stk->u.set & (1 << i)))
		i++;
	    if (OUTSIDE)
		stk->u.set = stk->u.set & ~(1 << i);
	    else
		UNARY(SET_NEWNODE, stk->u.set & ~(1 << i));
	    break;
	}
    case STRING_:
	 {
	    char *str = stk->u.str;
	    CHECKEMPTYSTRING(str, "rest");
	    if (OUTSIDE)
		stk->u.str = ++str;
	    else
		UNARY(STRING_NEWNODE, ++str);
	    break;
	}
    case LIST_:
	CHECKEMPTYLIST(stk->u.lis, "rest");
	if (OUTSIDE)
	    stk->u.lis = stk->u.lis->next;
	else
	    UNARY(LIST_NEWNODE, stk->u.lis->next);
	return;
    default:
	BADAGGREGATE("rest");
    }
}
