/*
    module  : ifstring.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef IFSTRING_C
#define IFSTRING_C

/**
Q2  OK  2650  ifstring  :  DDDP  X [T] [E]  ->  ...
If X is a string, executes T else executes E.
*/
void ifstring_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    node = pvec_lst(env->stck);
    node = node.op == STRING_ ? first : second;
    prog(env, node.u.lis);
}
#endif
