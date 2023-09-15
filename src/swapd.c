/*
    module  : swapd.c
    version : 1.5
    date    : 09/15/23
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
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    lst_push(env->stck, second);
    lst_push(env->stck, first);
    lst_push(env->stck, third);
}
#endif
