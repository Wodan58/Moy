/*
    module  : swapd.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef SWAPD_C
#define SWAPD_C

/**
Q0  OK  1280  swapd  :  DDDAAA  X Y Z  ->  Y X Z
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
