/*
    module  : ifchar.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef IFCHAR_C
#define IFCHAR_C

/**
Q2  OK  2620  ifchar  :  DDDP  X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
void ifchar_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    node = pvec_lst(env->stck);
    node = node.op == CHAR_ ? first : second;
    prog(env, node.u.lis);
}
#endif
