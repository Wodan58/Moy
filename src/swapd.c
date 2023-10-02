/*
    module  : swapd.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef SWAPD_C
#define SWAPD_C

/**
OK 1280  swapd  :  DDDAAA	X Y Z  ->  Y X Z
As if defined by:   swapd  ==  [swap] dip
*/
void swapd_(pEnv env)
{
    Node first, second, third;

    PARM(3, ANYTYPE);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    env->stck = pvec_add(env->stck, second);
    env->stck = pvec_add(env->stck, first);
    env->stck = pvec_add(env->stck, third);
}
#endif
