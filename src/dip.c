/*
    module  : dip.c
    version : 1.5
    date    : 09/11/23
*/
#ifndef DIP_C
#define DIP_C

/**
OK 2430  dip  :  DDAP	X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
PRIVATE void dip_(pEnv env)
{
#ifndef COMPILER
    Node list, node;

    PARM(2, DIP);
    list = lst_pop(env->stck);
    node = lst_pop(env->stck);
    prime(env, node);
    prog(env, list.u.lis);
#endif
}
#endif
