/*
    module  : condlinrec.c
    version : 1.5
    date    : 10/04/16
*/
#include <assert.h>
#include "interp.h"

/*
condlinrec  :  [ [C1] [C2] .. [D] ]  ->  ...
Each [Ci] is of the form [[B] [T]] or [[B] [R1] [R2]].
Tries each B. If that yields true and there is just a [T], executes T and exit.
If there are [R1] and [R2], executes R1, recurses, executes R2.
Subsequent case are ignored. If no B yields true, then [D] is used.
It is then of the form [[T]] or [[R1] [R2]]. For the former, executes T.
For the latter executes R1, recurses, executes R2.
*/
/* condlinrec.c */
PRIVATE void condlinrecaux(Node *root)
{
    int num = 0;
    Node *cur, *list, *save;

    for (cur = root; cur && cur->next; cur = cur->next) {
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
    cur = num ? cur->u.lis->next : cur->u.lis;
    exeterm(cur->u.lis);
    if ((cur = cur->next) != 0) {
	condlinrecaux(root);
	exeterm(cur->u.lis);
    }
}

PRIVATE void condlinrec_(void)
{
    Node *list;

    ONEPARAM("condlinrec");
    LIST("condlinrec");
    CHECKEMPTYLIST(stk->u.lis, "condlinrec");
    list = stk->u.lis;
    POP(stk);
    condlinrecaux(list);
}
