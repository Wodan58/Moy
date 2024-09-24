/*
    module  : i.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef I_C
#define I_C

/**
Q1  OK  2410  i  :  DP  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
void i_(pEnv env)
{
    Node node;

    PARM(1, DIP);
    node = vec_pop(env->stck);
    prog(env, node.u.lis);
}
#endif
