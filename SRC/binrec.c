/*
    module  : binrec.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
binrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
/* binrec.c */
PRIVATE void binrecaux(Node *first, Node *second, Node *third, Node *fourth)
{
    int num;
    Node *save, node;

    save = stk;
    CONDITION;
    exeterm(first);
    num = stk->u.num;
    RELEASE;
    stk = save;
    if (num)
	exeterm(second);
    else {
	exeterm(third);
	node = *stk;
	POP(stk);
	binrecaux(first, second, third, fourth);
	DUPLICATE(&node);
	binrecaux(first, second, third, fourth);
	exeterm(fourth);
    }
}

PRIVATE void binrec_(void)
{
    Node *first, *second, *third, *fourth;

    FOURPARAMS("binrec");
    FOURQUOTES("binrec");
    fourth = stk->u.lis;
    POP(stk);
    third = stk->u.lis;
    POP(stk);
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    binrecaux(first, second, third, fourth);
}
