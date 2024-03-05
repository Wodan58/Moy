/*
    module  : iflist.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef IFLIST_C
#define IFLIST_C

/**
Q2  OK  2660  iflist  :  DDDP  X [T] [E]  ->  ...
If X is a list, executes T else executes E.
*/
void iflist_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    node = pvec_lst(env->stck);
    node = node.op == LIST_ ? first : second;
    prog(env, node.u.lis);
}
#endif
