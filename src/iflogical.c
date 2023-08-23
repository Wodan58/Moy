/*
    module  : iflogical.c
    version : 1.3
    date    : 08/23/23
*/
#ifndef IFLOGICAL_C
#define IFLOGICAL_C

/**
OK 2650  iflogical  :  DDDP	X [T] [E]  ->  ...
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
