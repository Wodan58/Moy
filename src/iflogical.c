/*
    module  : iflogical.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef IFLOGICAL_C
#define IFLOGICAL_C

/**
Q2  OK  2630  iflogical  :  DDDP  X [T] [E]  ->  ...
If X is a logical or truth value, executes T else executes E.
*/
void iflogical_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    node = pvec_lst(env->stck);
    node = node.op == BOOLEAN_ ? first : second;
    prog(env, node.u.lis);
}
#endif
