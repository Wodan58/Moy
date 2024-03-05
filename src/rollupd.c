/*
    module  : rollupd.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef ROLLUPD_C
#define ROLLUPD_C

/**
Q0  OK  1290  rollupd  :  DDDDAAAA  X Y Z W  ->  Z X Y W
As if defined by:   rollupd  ==  [rollup] dip
*/
void rollupd_(pEnv env)
{
    Node first, second, third, fourth;

    PARM(4, ANYTYPE);
    env->stck = pvec_pop(env->stck, &fourth);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    env->stck = pvec_add(env->stck, third);
    env->stck = pvec_add(env->stck, first);
    env->stck = pvec_add(env->stck, second);
    env->stck = pvec_add(env->stck, fourth);
}
#endif
