/*
    module  : condnestrec.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
condnestrec  :  [ [C1] [C2] .. [D] ]  ->  ...
A generalisation of condlinrec.
Each [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form
[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].
For the case taken, executes each [Ri] but recurses between any two
consecutive [Ri] (n > 3 would be exceptional.)
*/
/* condnestrec.c */
PRIVATE void condnestrecaux(Node *root)
{
    int num = 0;
    Node *cur, *save = stk;

    CONDITION;
    for (cur = root; cur && cur->next; cur = cur->next) {
	stk = save;
	exeterm(cur->u.lis->u.lis);
	if ((num = stk->u.num) != 0)
	    break;
    }
    RELEASE;
    stk = save;
    cur = num ? cur->u.lis->next : cur->u.lis;
    exeterm(cur->u.lis);
    for (cur = cur->next; cur; cur = cur->next) {
	condnestrecaux(root);
	exeterm(cur->u.lis);
    }
}

PRIVATE void condnestrec_(void)
{
    Node *list;

    ONEPARAM("condnestrec");
    LIST("condnestrec");
    CHECKEMPTYLIST(stk->u.lis, "condnestrec");
    list = stk->u.lis;
    POP(stk);
    condnestrecaux(list);
}
