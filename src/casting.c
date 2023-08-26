/*
    module  : casting.c
    version : 1.3
    date    : 08/26/23
*/
#ifndef CASTING_C
#define CASTING_C

/**
OK 2326  casting  :  DDA 	X Y  ->  Z
Z takes the value from X and the type from Y.
*/
void casting_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    first.op = second.op;
    lst_push(env->stck, first);
}
#endif
