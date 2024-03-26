/*
    module  : dip.c
    version : 1.10
    date    : 03/21/24
*/
#ifndef DIP_C
#define DIP_C

/**
Q1  OK  2430  dip  :  DDPA  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
void dip_(pEnv env)
{
    Node list, node;

    PARM(2, DIP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &node);
    prime(env, node);
    prog(env, list.u.lis);
}
#endif
