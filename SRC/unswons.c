/*
    module  : unswons.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
unswons  :  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
/* unswons.c */
PRIVATE void unswons_(void)
{
    Node save;

    ONEPARAM("unswons");
    switch (stk->op) {
    case SET_:
	 {
	    int i = 0;
	    long_t set = stk->u.set;
	    CHECKEMPTYSET(set, "unswons");
	    while (!(set & (1 << i)))
		i++;
	    if (OUTSIDE)
		stk->u.set = set & ~(1 << i);
	    else
		UNARY(SET_NEWNODE, set & ~(1 << i));
	    PUSH(INTEGER_, (long_t)i);
	    break;
	}
    case STRING_:
	 {
	    char *str = stk->u.str;
	    CHECKEMPTYSTRING(str, "unswons");
	    if (OUTSIDE)
		stk->u.str = str + 1;
	    else
		UNARY(STRING_NEWNODE, str + 1);
	    PUSH(CHAR_, (long_t)*str);
	    break;
	}
    case LIST_:
	save = *stk;
	CHECKEMPTYLIST(stk->u.lis, "unswons");
	if (OUTSIDE)
	    stk->u.lis = stk->u.lis->next;
	else
	    UNARY(LIST_NEWNODE, stk->u.lis->next);
	DUPLICATE(save.u.lis);
	return;
    default:
	BADAGGREGATE("unswons");
    }
}
