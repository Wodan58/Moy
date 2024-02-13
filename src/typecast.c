/*
    module  : typecast.c
    version : 1.1
    date    : 01/18/24
*/
#ifndef TYPECAST_C
#define TYPECAST_C

/**
OK 3250  typecast  :  X Y  ->  Z
[EXT] Z takes the value from X and uses the value from Y as its type.
*/
void typecast_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first.op = second.u.num;
    env->stck = pvec_add(env->stck, first);
}
#endif
