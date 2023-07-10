/*
    module  : iflogical.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef IFLOGICAL_C
#define IFLOGICAL_C

/**
OK 2650  iflogical  :  DDDU	X [T] [E]  ->  ...
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
