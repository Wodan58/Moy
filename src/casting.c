/*
    module  : casting.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef CASTING_C
#define CASTING_C

/**
OK 3200  casting  :  DDA 	X Y  ->  Z
Z takes the value from X and the type from Y.
*/
void casting_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first.op = second.op;
    vec_push(env->stck, first);
}
#endif
