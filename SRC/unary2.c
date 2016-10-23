/*
    module  : unary2.c
    version : 1.6
    date    : 10/08/16
*/
#include "interp.h"

/*
unary2  :  X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
/* unary2.c */
PRIVATE void unary2_(void)
{
    Node *prog, temp, *top, result[2];
#ifdef ARITY
    int d;
#endif

    THREEPARAMS("unary2");
    ONEQUOTE("unary2");
    prog = stk->u.lis;
    POP(stk);
    temp = *stk;
    POP(stk);
    top = stk->next;
#ifdef ARITY
    copy_(d = arity(prog));
#else 
    CONDITION;
#endif
    exeterm(prog);
    result[0] = *stk;
#ifndef ARITY
    RELEASE;
#endif
    stk = top;
    DUPLICATE(&temp);
#ifdef ARITY
    copy_(d);
#else
    CONDITION;
#endif
    exeterm(prog);
    result[1] = *stk;
#ifndef ARITY
    RELEASE;
#endif
    stk = top;
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
}
