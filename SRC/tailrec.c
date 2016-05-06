/*
    module  : tailrec.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
tailrec  :  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
/* tailrec.c */
PRIVATE void tailrecaux(Node *first, Node *second, Node *third)
{
   int num;
   Node *save;

tailrec:
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
    tailrecaux(first, second, third);
}
