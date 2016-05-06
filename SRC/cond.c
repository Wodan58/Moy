/*
    module  : cond.c
    version : 1.2
    date    : 05/06/16
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
    Node *cur, *save;

    ONEPARAM("cond");
/* must check for QUOTES in list */
    LIST("cond");
    CHECKEMPTYLIST(stk->u.lis, "cond");
    cur = stk->u.lis;
    POP(stk);
    save = stk;
    CONDITION;
    for ( ; cur && cur->next; cur = cur->next) {
	stk = save;
	exeterm(cur->u.lis->u.lis);
	if ((num = stk->u.num) != 0)
	    break;
    }
    RELEASE;
    stk = save;
    exeterm(num ? cur->u.lis->next : cur->u.lis);
}
