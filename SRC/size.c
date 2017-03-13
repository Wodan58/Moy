/*
    module  : size.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
size  :  A  ->  I
Integer I is the number of elements of aggregate A.
*/
PRIVATE void do_size(void)
{
    int i;
    Node *cur;
    size_t size = 0;

#ifndef NCHECK
    if (optimizing && AGGREGATE(stk))
	;
    else
	COMPILE;
    ONEPARAM("size");
#endif
    switch (stk->op) {
    case LIST_:
	for (cur = stk->u.lis; cur; cur = cur->next)
	    size++;
	break;
    case STRING_:
	size = strlen(stk->u.str);
	break;
    case SET_:
	for (i = 0; i < SETSIZE_; i++)
	    if (stk->u.set & (1 << i))
		size++;
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("size");
#endif
    }
    if (OUTSIDE) {
	stk->u.num = size;
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, size);
}
