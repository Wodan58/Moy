/*
    module  : rollupd.c
    version : 1.8
    date    : 09/17/24
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
    fourth = vec_pop(env->stck);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    vec_push(env->stck, third);
    vec_push(env->stck, first);
    vec_push(env->stck, second);
    vec_push(env->stck, fourth);
}
#endif
