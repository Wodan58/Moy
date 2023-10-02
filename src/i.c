/*
    module  : i.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef I_C
#define I_C

/**
OK 2410  i  :  DP	[P]  ->  ...
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
