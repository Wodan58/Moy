/*
    module  : opcase.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
opcase  :  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
PRIVATE void do_opcase(void)
{
    Node *cur;

#ifndef NCHECK
    if (optimizing && LIST_1 && VALID(stk->next))
	;
    else
	COMPILE;
    ONEPARAM("opcase");
    LIST("opcase");
    CHECKEMPTYLIST(stk->u.lis, "opcase");
#endif
    for (cur = stk->u.lis; cur->next && cur->op == LIST_; cur = cur->next)
	if (cur->u.lis->op == stk->next->op)
	    if (cur->u.lis->op != ANON_FUNCT_ ||
		cur->u.lis->u.proc == stk->next->u.proc)
		break;
#ifndef NCHECK
    CHECKLIST(cur->op, "opcase");
#endif
    cur = cur->next ? cur->u.lis->next : cur->u.lis;
    if (OUTSIDE) {
	stk->u.lis = cur;
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, cur);
}
