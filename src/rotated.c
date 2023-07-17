/*
    module  : rotated.c
    version : 1.2
    date    : 07/17/23
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
    fourth = vec_pop(env->stck);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    vec_push(env->stck, third);
    vec_push(env->stck, second);
    vec_push(env->stck, first);
    vec_push(env->stck, fourth);
}
#endif
