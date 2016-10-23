/*
    module  : cond.c
    version : 1.5
    date    : 10/04/16
*/
#include "interp.h"

/*
cond  :  [..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
/* cond.c */
PRIVATE void cond_(void)
{
    int num = 0;
    Node *cur, *list, *save;

    ONEPARAM("cond");
/* must check for QUOTES in list */
    LIST("cond");
    CHECKEMPTYLIST(stk->u.lis, "cond");
    cur = stk->u.lis;
    POP(stk);
    for ( ; cur->next; cur = cur->next) {
	list = cur->u.lis->u.lis;
	save = stk;
#ifdef ARITY
	copy_(arity(list));
#else
	CONDITION;
#endif
	exeterm(list);
	num = stk->u.num;
	stk = save;
#ifndef ARITY
	RELEASE;
#endif
	if (num)
	    break;
    }
    exeterm(num ? cur->u.lis->next : cur->u.lis);
}
