/*
    module  : unary3.c
    version : 1.5
    date    : 10/04/16
*/
#include "interp.h"

/*
unary3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
/* unary3.c */
PRIVATE void unary3_(void)
{
    Node *prog, first, second, *top, result[3];
#ifdef ARITY
    int d;
#endif

    FOURPARAMS("unary3");
    ONEQUOTE("unary3");
    prog = stk->u.lis;
    POP(stk);
    second = *stk;
    POP(stk);
    first = *stk;
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
    DUPLICATE(&first);
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
    DUPLICATE(&second);
#ifdef ARITY
    copy_(d);
#else
    CONDITION;
#endif
    exeterm(prog);
    result[2] = *stk;
#ifndef ARITY
    RELEASE;
#endif
    stk = top;
    DUPLICATE(&result[0]);
    DUPLICATE(&result[1]);
    DUPLICATE(&result[2]);
}
