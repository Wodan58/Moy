/*
    module  : ifset.c
    version : 1.3
    date    : 08/23/23
*/
#ifndef IFSET_C
#define IFSET_C

/**
OK 2660  ifset  :  DDDP	X [T] [E]  ->  ...
If X is a set, executes T else executes E.
*/
void ifset_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == SET_ ? first : second;
    prog(env, node.u.lis);
}
#endif
