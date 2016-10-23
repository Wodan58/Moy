/*
    module  : binrec.c
    version : 1.5
    date    : 10/04/16
*/
#include "interp.h"

/*
binrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
/* binrec.c */
#ifdef ARITY
PRIVATE void binrecaux(int d,Node *first,Node *second,Node *third,Node *fourth)
#else
PRIVATE void binrecaux(Node *first, Node *second, Node *third, Node *fourth)
#endif
{
    int num;
    Node *save, temp;

    save = stk;
#ifdef ARITY
    copy_(d);
#else
    CONDITION;
#endif
    exeterm(first);
    num = stk->u.num;
    stk = save;
#ifndef ARITY
    RELEASE;
#endif
    if (num)
	exeterm(second);
    else {
	exeterm(third);
	temp = *stk;
	POP(stk);
#ifdef ARITY
	binrecaux(d, first, second, third, fourth);
#else
	binrecaux(first, second, third, fourth);
#endif
	DUPLICATE(&temp);
#ifdef ARITY
	binrecaux(d, first, second, third, fourth);
#else
	binrecaux(first, second, third, fourth);
#endif
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
#ifdef ARITY
    binrecaux(arity(first), first, second, third, fourth);
#else
    binrecaux(first, second, third, fourth);
#endif
}
