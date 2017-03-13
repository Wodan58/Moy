/*
    module  : drop.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
drop  :  A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
PRIVATE void do_drop(void)
{
    int i, num;
    Node *node;
    ulong_t set;

#ifndef NCHECK
    if (optimizing && INTEGER_1 && AGGREGATE(stk->next))
	;
    else
	COMPILE;
    TWOPARAMS("drop");
#endif
    num = stk->u.num;
    POP(stk);
    switch (stk->op) {
    case LIST_:
	node = stk->u.lis;
	while (num-- > 0 && node)
	    node = node->next;
	if (OUTSIDE)
	    stk->u.lis = node;
	else
	    UNARY(LIST_NEWNODE, node);
	break;
    case STRING_:
	if (OUTSIDE)
	    stk->u.str += num;
	else
	    UNARY(STRING_NEWNODE, (stk->u.str + num));
	break;
    case SET_:
	for (set = i = 0; i < SETSIZE_; i++)
	    if (stk->u.set & (1 << i)) {
		if (num < 1)
		    set |= 1 << i;
		else
		    num--;
	    }
	if (OUTSIDE)
	    stk->u.set = set;
	else
	    UNARY(SET_NEWNODE, set);
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("drop");
#endif
    }
}
