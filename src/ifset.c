/*
    module  : ifset.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef IFSET_C
#define IFSET_C

/**
Q2  OK  2640  ifset  :  DDDP  X [T] [E]  ->  ...
If X is a set, executes T else executes E.
*/
void ifset_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == SET_ ? first : second;
    prog(env, node.u.lis);
}
#endif
