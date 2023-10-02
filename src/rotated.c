/*
    module  : rotated.c
    version : 1.7
    date    : 10/02/23
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
    env->stck = pvec_pop(env->stck, &fourth);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    env->stck = pvec_add(env->stck, third);
    env->stck = pvec_add(env->stck, second);
    env->stck = pvec_add(env->stck, first);
    env->stck = pvec_add(env->stck, fourth);
}
#endif
