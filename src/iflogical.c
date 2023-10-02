/*
    module  : iflogical.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef IFLOGICAL_C
#define IFLOGICAL_C

/**
OK 2630  iflogical  :  DDDP	X [T] [E]  ->  ...
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
