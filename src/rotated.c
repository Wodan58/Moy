/*
    module  : rotated.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef ROTATED_C
#define ROTATED_C

/**
OK 1310  rotated  :  DDDDAAAA	X Y Z W  ->  Z Y X W
As if defined by:   rotated  ==  [rotate] dip
*/
void rotated_(pEnv env)
{
    Node first, second, third, fourth;

    PARM(4, ANYTYPE);
    fourth = lst_pop(env->stck);
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    lst_push(env->stck, third);
    lst_push(env->stck, second);
    lst_push(env->stck, first);
    lst_push(env->stck, fourth);
}
#endif
