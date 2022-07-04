/*
    module  : i.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef I_C
#define I_C

/**
i  :  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
PRIVATE void do_i(pEnv env)
{
    Node *prog;

    ONEPARAM("i");
    ONEQUOTE("i");
    prog = env->stk->u.lis;
    POP(env->stk);
    exeterm(env, prog);
}
#endif
