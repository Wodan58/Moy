/*
    module  : iflogical.c
    version : 1.9
    date    : 09/17/24
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
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == BOOLEAN_ ? first : second;
    prog(env, node.u.lis);
}
#endif
