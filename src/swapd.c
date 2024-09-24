/*
    module  : swapd.c
    version : 1.8
    date    : 09/17/24
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
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    vec_push(env->stck, second);
    vec_push(env->stck, first);
    vec_push(env->stck, third);
}
#endif
