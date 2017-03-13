/*
    module  : take.c
    version : 1.6
    date    : 03/12/17
*/
#include "runtime.h"

/*
take  :  A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
PRIVATE void do_take(void)
{
    char *str;
    int i, num;
    ulong_t set;
    Node *root = 0, *cur, *last;

#ifndef NCHECK
    if (optimizing && INTEGER_1 && AGGREGATE(stk->next))
	;
    else
	COMPILE;
    TWOPARAMS("take");
#endif
    num = stk->u.num;
    POP(stk);
    switch (stk->op) {
    case LIST_:
	if (num < 1) {
	    if (OUTSIDE)
		stk->u.lis = 0;
	    else
		UNARY(LIST_NEWNODE, 0);
	} else {
	    for (cur = stk->u.lis; cur && num-- > 0; cur = cur->next)
		if (!root)
		    last = root = heapnode(cur->op, cur->u.ptr, 0);
		else
		    last = last->next = heapnode(cur->op, cur->u.ptr, 0);
	    if (OUTSIDE)
		stk->u.lis = root;
	    else
		UNARY(LIST_NEWNODE, root);
	}
	break;
    case STRING_:
	str = GC_malloc_atomic(num + 1);
	strncpy(str, stk->u.str, num);
	str[num] = 0;
	if (OUTSIDE)
	    stk->u.str = str;
	else
	    UNARY(STRING_NEWNODE, str);
	break;
    case SET_:
	for (set = i = 0; i < SETSIZE_; i++)
	    if (stk->u.set & (1 << i)) {
		if (num-- > 0)
		    set |= 1 << i;
		else
		    break;
	    }
	if (OUTSIDE)
	    stk->u.set = set;
	else
	    UNARY(SET_NEWNODE, set);
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("take");
#endif
    }
}
