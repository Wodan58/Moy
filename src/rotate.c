/*
    module  : rotate.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef ROTATE_C
#define ROTATE_C

/**
OK 1250  rotate  :  DDDAAA 	X Y Z  ->  Z Y X
Interchanges X and Z.
*/
void rotate_(pEnv env)
{
    Node first, second, third;

    PARM(3, ANYTYPE);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    env->stck = pvec_add(env->stck, third);
    env->stck = pvec_add(env->stck, second);
    env->stck = pvec_add(env->stck, first);
}
#endif
