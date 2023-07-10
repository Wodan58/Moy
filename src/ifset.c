/*
    module  : ifset.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef IFSET_C
#define IFSET_C

/**
OK 2660  ifset  :  DDDU	X [T] [E]  ->  ...
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
