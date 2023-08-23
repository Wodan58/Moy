/*
    module  : i.c
    version : 1.3
    date    : 08/23/23
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
    node = lst_pop(env->stck);
    prog(env, node.u.lis);
}
#endif
