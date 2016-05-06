/*
    module  : opcase.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
opcase  :  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
/* opcase.c */
PRIVATE void opcase_(void)
{
    Node *cur;

    ONEPARAM("opcase");
    LIST("opcase");
    cur = stk->u.lis;
    CHECKEMPTYLIST(cur, "opcase");
    while (cur->next && cur->op == LIST_ && cur->u.lis->op != stk->next->op)
	cur = cur->next;
    CHECKLIST(cur->op, "opcase");
    if (OUTSIDE) {
	stk->u.lis = cur->next ? cur->u.lis->next : cur->u.lis;
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, cur->next ? cur->u.lis->next : cur->u.lis);
}
