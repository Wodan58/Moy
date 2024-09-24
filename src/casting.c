/*
    module  : casting.c
    version : 1.12
    date    : 09/17/24
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
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first.op = second.u.num;
    vec_push(env->stck, first);
}
#endif
