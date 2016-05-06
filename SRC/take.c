/*
    module  : take.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
take  :  A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
/* take.c */
PRIVATE void take_(void)
{
    Node *cur = 0;
    Node *root = 0;
    Node *last = 0;
    int i, num;

    TWOPARAMS("take");
    num = stk->u.num;
    POP(stk);
    switch (stk->op) {
    case SET_:
	{
	    long_t result = 0;
	    for (i = 0; i < SETSIZE; i++)
		if (stk->u.set & (1 << i)) {
		    if (num-- > 0)
			result |= 1 << i;
		    else
			break;
		}
	    if (OUTSIDE)
		stk->u.set = result;
	    else
		UNARY(SET_NEWNODE, result);
	    return;
	}
    case STRING_:
	{
	    char *ptr, *str = stk->u.str;
	    if (num < 0)
		num = 0;
	    if ((size_t)num > strlen(str))
		return;
	    ptr = GC_malloc(num + 1);
	    strncpy(ptr, str, num);
	    ptr[num] = 0;
	    if (OUTSIDE)
		stk->u.str = ptr;
	    else
		UNARY(STRING_NEWNODE, ptr);
	    return;
	}
    case LIST_:
	{
	    if (num < 1) {
		if (OUTSIDE)
		    stk->u.lis = 0;
		else
		    BINARY(LIST_NEWNODE, 0);
		return;
	    }
	    for (cur = stk->u.lis; cur && num-- > 0; cur = cur->next)
		if (!root)
		    last = root = newnode(cur->op, cur->u.ptr, 0);
		else
		    last = last->next = newnode(cur->op, cur->u.ptr, 0);
	    if (OUTSIDE)
		stk->u.lis = root;
	    else
		UNARY(LIST_NEWNODE, root);
	    return;
	}
    default:
	BADAGGREGATE("take");
    }
}
