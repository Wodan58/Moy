/*
    module  : rollup.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef ROLLUP_C
#define ROLLUP_C

/**
OK 1230  rollup  :  DDDAAA 	X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
void rollup_(pEnv env)
{
    Node first, second, third;

    PARM(3, ANYTYPE);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    env->stck = pvec_add(env->stck, third);
    env->stck = pvec_add(env->stck, first);
    env->stck = pvec_add(env->stck, second);
}
#endif
