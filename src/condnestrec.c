/*
    module  : condnestrec.c
    version : 1.13
    date    : 03/28/20
*/
#ifndef CONDNESTREC_C
#define CONDNESTREC_C

#ifdef CONDLINREC_X
#undef CONDLINREC_X
#undef CONDLINREC_C
#endif

#include "condlinrec.c"

#ifndef OLD_RUNTIME
int put_condnestrec(void);
#endif

/**
condnestrec  :  [ [C1] [C2] .. [D] ]  ->  ...
A generalisation of condlinrec.
Each [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form
[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].
For the case taken, executes each [Ri] but recurses between any two
consecutive [Ri] (n > 3 would be exceptional.)
*/
PRIVATE void do_condnestrec(void)
{
    Node *prog;

#ifndef OLD_RUNTIME
    if (compiling && put_condnestrec())
	return;
    COMPILE;
#endif
    ONEPARAM("condnestrec");
    LIST("condnestrec");
    CHECKEMPTYLIST(stk->u.lis, "condnestrec");
    prog = stk->u.lis;
    POP(stk);
    condnestrec(prog);
}
#endif
