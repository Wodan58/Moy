/*
    module  : ifset.c
    version : 1.5
    date    : 09/11/23
*/
#ifndef IFSET_C
#define IFSET_C

/**
OK 2640  ifset  :  DDDP	X [T] [E]  ->  ...
If X is a set, executes T else executes E.
*/
void ifset_(pEnv env)
{
#ifndef COMPILER
    Node first, second, node;

    PARM(3, WHILE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == SET_ ? first : second;
    prog(env, node.u.lis);
#endif
}
#endif
