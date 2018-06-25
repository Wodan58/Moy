/*
    module  : index.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
index  :  I A  ->  X
X (= A[I]) is the member of A at position I (I = 0,1).
*/
PRIVATE void do_index(void)
{
    Node *list;

#ifndef NCHECK
    unsigned op, op1;

    if (optimizing) {
	op = pop_history(&op1);
	del_history(1);
	if (op == LIST_)
	    add_history(op1);
	else if (op == STRING_)
	    add_history(CHAR_);
	else
	    add_history(INTEGER_);
    }
    COMPILE;
    TWOPARAMS("index");
#endif
    list = stk->u.lis;
    if (stk->next->u.num)
	list = list->next;
    if (OUTSIDE) {
	POP(stk);
	stk->op = list->op;
	stk->u = list->u;
    } else
	GBINARY(list->op, list->u.ptr);
}
