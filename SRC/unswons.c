/*
    module  : unswons.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
unswons  :  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
PRIVATE void do_unswons(void)
{
    char *str;
    int i = 0;
    Node *save;
    ulong_t set;

#ifndef NCHECK
    COMPILE;
    ONEPARAM("unswons");
#endif
    switch (stk->op) {
    case LIST_:
#ifndef NCHECK
	CHECKEMPTYLIST(stk->u.lis, "unswons");
#endif
	save = stk->u.lis;
	if (OUTSIDE)
	    stk->u.lis = stk->u.lis->next;
	else
	    UNARY(LIST_NEWNODE, stk->u.lis->next);
	DUPLICATE(save);
	break;
    case STRING_:
	str = stk->u.str;
#ifndef NCHECK
	CHECKEMPTYSTRING(str, "unswons");
#endif
	if (OUTSIDE)
	    stk->u.str = str + 1;
	else
	    UNARY(STRING_NEWNODE, (str + 1));
	PUSH(CHAR_, (long_t)*str);
	break;
    case SET_:
	set = stk->u.set;
#ifndef NCHECK
	CHECKEMPTYSET(set, "unswons");
#endif
	while (!(set & (1 << i)))
	    i++;
	if (OUTSIDE)
	    stk->u.set = set & ~(1 << i);
	else
	    UNARY(SET_NEWNODE, set & ~(1 << i));
	PUSH(INTEGER_, i);
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("unswons");
#endif
    }
}
