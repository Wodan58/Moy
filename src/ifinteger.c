/*
    module  : ifinteger.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef IFINTEGER_C
#define IFINTEGER_C

/**
Q2  OK  2610  ifinteger  :  DDDP  X [T] [E]  ->  ...
If X is an integer, executes T else executes E.
*/
void ifinteger_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    node = pvec_lst(env->stck);
    node = node.op == INTEGER_ ? first : second;
    prog(env, node.u.lis);
}
#endif
