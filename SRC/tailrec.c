/*
    module  : tailrec.c
    version : 1.5
    date    : 10/04/16
*/
#include "interp.h"

/*
tailrec  :  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
/* tailrec.c */
#ifdef ARITY
PRIVATE void tailrecaux(int d, Node *first, Node *second, Node *third)
#else
PRIVATE void tailrecaux(Node *first, Node *second, Node *third)
#endif
{
    int num;
    Node *save;

tailrec:
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
	goto tailrec;
    }
}

PRIVATE void tailrec_(void)
{
    Node *first, *second, *third;

    THREEPARAMS("tailrec");
    THREEQUOTES("tailrec");
    third = stk->u.lis;
    POP(stk);
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
#ifdef ARITY
    tailrecaux(arity(first), first, second, third);
#else
    tailrecaux(first, second, third);
#endif
}
