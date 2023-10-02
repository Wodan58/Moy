/*
    module  : dup.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef DUP_C
#define DUP_C

/**
OK 1210  dup  :  A 	X  ->  X X
Pushes an extra copy of X onto stack.
*/
void dup_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = pvec_lst(env->stck);
    env->stck = pvec_add(env->stck, node);
}
#endif
