/*
    module  : condnestrec.c
    version : 1.15
    date    : 06/20/22
*/
#ifndef CONDNESTREC_C
#define CONDNESTREC_C

#ifdef CONDLINREC_X
#undef CONDLINREC_X
#undef CONDLINREC_C
#endif

#include "condlinrec.c"

/**
condnestrec  :  [ [C1] [C2] .. [D] ]  ->  ...
A generalisation of condlinrec.
Each [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form
[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].
For the case taken, executes each [Ri] but recurses between any two
consecutive [Ri] (n > 3 would be exceptional.)
*/
PRIVATE void do_condnestrec(pEnv env)
{
    Node *prog;

    ONEPARAM("condnestrec");
    LIST("condnestrec");
    prog = env->stk->u.lis;
    CHECKEMPTYLIST(prog, "condnestrec");
    POP(env->stk);
    INSTANT(put_condnestrec);
    condnestrec(env, prog);
}
#endif
