/*
    module  : ifset.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef IFSET_C
#define IFSET_C

/**
OK 2640  ifset  :  DDDP	X [T] [E]  ->  ...
If X is a set, executes T else executes E.
*/
void ifset_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    node = pvec_lst(env->stck);
    node = node.op == SET_ ? first : second;
    prog(env, node.u.lis);
}
#endif
