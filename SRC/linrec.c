/*
    module  : linrec.c
    version : 1.5
    date    : 10/04/16
*/
#include "interp.h"

/*
linrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
/* linrec.c */
#ifdef ARITY
PRIVATE void linrecaux(int d,Node *first,Node *second,Node *third,Node *fourth)
#else
PRIVATE void linrecaux(Node *first, Node *second, Node *third, Node *fourth)
#endif
{
    int num;
    Node *save;

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
#ifdef ARITY
	linrecaux(d, first, second, third, fourth);
#else
	linrecaux(first, second, third, fourth);
#endif
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
#ifdef ARITY
    linrecaux(arity(first), first, second, third, fourth);
#else
    linrecaux(first, second, third, fourth);
#endif
}
