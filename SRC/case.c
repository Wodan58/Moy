/*
    module  : case.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
case  :  X [..[X Y]..]  ->  Y i
Indexing on the value of X, execute the matching Y.
*/
/* case.c */
PRIVATE void case_(void)
{
    Node *cur;
    int error;

    TWOPARAMS("case");
    LIST("case");
    cur = stk->u.lis;
    CHECKEMPTYLIST(cur, "case");
    POP(stk);
    for ( ; cur->next; cur = cur->next)
	if (!Compare(cur->u.lis, stk, &error) && !error)
	    break;
    if (cur->next) {
	POP(stk);
	exeterm(cur->u.lis->next);
    } else
	exeterm(cur->u.lis);
}
