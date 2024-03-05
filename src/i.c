/*
    module  : i.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef I_C
#define I_C

/**
Q1  OK  2410  i  :  DP  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
PRIVATE void i_(pEnv env)
{
    Node node;

    PARM(1, DIP);
    env->stck = pvec_pop(env->stck, &node);
    prog(env, node.u.lis);
}
#endif
