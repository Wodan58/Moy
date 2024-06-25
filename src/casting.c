/*
    module  : casting.c
    version : 1.11
    date    : 06/22/24
*/
#ifndef CASTING_C
#define CASTING_C

/**
Q0  OK  3150  casting  :  DDA  X Y  ->  Z
[EXT] Z takes the value from X and uses the value from Y as its type.
*/
void casting_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first.op = second.u.num;
    env->stck = pvec_add(env->stck, first);
}
#endif
