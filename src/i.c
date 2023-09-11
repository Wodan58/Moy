/*
    module  : i.c
    version : 1.5
    date    : 09/11/23
*/
#ifndef I_C
#define I_C

/**
OK 2410  i  :  DP	[P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
PRIVATE void i_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, DIP);
    node = lst_pop(env->stck);
    prog(env, node.u.lis);
#endif
}
#endif
