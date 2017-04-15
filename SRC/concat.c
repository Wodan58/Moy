/*
    module  : concat.c
    version : 1.6
    date    : 04/09/17
*/
#include "runtime.h"

/*
concat  :  S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
PRIVATE void do_concat(void)
{
    char *str;
    unsigned i;
    Node *cur = 0, *root = 0, *last = 0;

#ifndef NCHECK
    if (optimizing)
	del_history(1);
    if (optimizing && stk->op == stk->next->op &&
	AGGREGATE(stk) && AGGREGATE(stk->next))
	;
    else
	COMPILE;
    TWOPARAMS("concat");
    SAME2TYPES("concat");
#endif
    switch (stk->op) {
    case LIST_:
	if (!stk->next->u.lis) {
	    if (OUTSIDE) {
		stk->next->u.lis = stk->u.lis;
		POP(stk);
	    } else
	        BINARY(LIST_NEWNODE, stk->u.lis);
	    return;
	}
	for (cur = stk->next->u.lis; cur; cur = cur->next)
	    if (!root)
		last = root = heapnode(cur->op, cur->u.ptr, 0);
	    else
		last = last->next = heapnode(cur->op, cur->u.ptr, 0);
	last->next = stk->u.lis;
	if (OUTSIDE) {
	    stk->next->u.lis = root;
	    POP(stk);
	} else
	    BINARY(LIST_NEWNODE, root);
	break;
    case STRING_:
	i = strlen(stk->next->u.str);
	str = GC_malloc_atomic(i + strlen(stk->u.str) + 1);
	strcpy(str, stk->next->u.str);
	strcpy(str + i, stk->u.str);
	if (OUTSIDE) {
	    stk->next->u.str = str;
	    POP(stk);
	} else
	    BINARY(STRING_NEWNODE, str);
	break;
    case SET_:
	if (OUTSIDE) {
	    stk->next->u.set |= stk->u.set;
	    POP(stk);
	} else
	    BINARY(SET_NEWNODE, stk->next->u.set | stk->u.set);
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("concat");
#endif
    }
}
