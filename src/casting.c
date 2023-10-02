/*
    module  : casting.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef CASTING_C
#define CASTING_C

/**
OK 3170  casting  :  DDA 	X Y  ->  Z
[EXT] Z takes the value from X and the type from Y.
*/
void casting_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first.op = second.op;
    env->stck = pvec_add(env->stck, first);
}
#endif
