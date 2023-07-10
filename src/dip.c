/*
    module  : dip.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef DIP_C
#define DIP_C

/**
OK 2450  dip  :  DDAU	X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
PRIVATE void dip_(pEnv env)
{
    Node list, node;

    PARM(2, DIP);
    list = vec_pop(env->stck);
    node = vec_pop(env->stck);
    prime(env, node);
    prog(env, list.u.lis);
}
#endif
