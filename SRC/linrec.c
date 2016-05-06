/*
    module  : linrec.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
linrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
/* linrec.c */
PRIVATE void linrecaux(Node *first, Node *second, Node *third, Node *fourth)
{
    int num;
    Node *save = stk;

    CONDITION;
    exeterm(first);
    num = stk->u.num;
    RELEASE;
    stk = save;
    if (num)
	exeterm(second);
    else {
	exeterm(third);
	linrecaux(first, second, third, fourth);
	exeterm(fourth);
    }
}

PRIVATE void linrec_(void)
{
    Node *first, *second, *third, *fourth;

    FOURPARAMS("linrec");
    FOURQUOTES("linrec");
    fourth = stk->u.lis;
    POP(stk);
    third = stk->u.lis;
    POP(stk);
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    linrecaux(first, second, third, fourth);
}
