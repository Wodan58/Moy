/*
    module  : iflogical.c
    version : 1.6
    date    : 09/15/23
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
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == BOOLEAN_ ? first : second;
    prog(env, node.u.lis);
}
#endif
