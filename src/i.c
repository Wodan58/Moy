/*
    module  : i.c
    version : 1.2
    date    : 07/17/23
*/
#ifndef I_C
#define I_C

/**
OK 2430  i  :  DP	[P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
PRIVATE void i_(pEnv env)
{
    Node node;

    PARM(1, DIP);
    node = vec_pop(env->stck);
    prog(env, node.u.lis);
}
#endif
