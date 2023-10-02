/*
    module  : rolldownd.c
    version : 1.6
    date    : 
*/
#ifndef ROLLDOWND_C
#define ROLLDOWND_C

/**
OK 1300  rolldownd  :  DDDDAAAA	X Y Z W  ->  Y Z X W
As if defined by:   rolldownd  ==  [rolldown] dip
*/
void rolldownd_(pEnv env)
{
    Node first, second, third, fourth;

    PARM(4, ANYTYPE);
    env->stck = pvec_pop(env->stck, &fourth);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    env->stck = pvec_add(env->stck, second);
    env->stck = pvec_add(env->stck, third);
    env->stck = pvec_add(env->stck, first);
    env->stck = pvec_add(env->stck, fourth);
}
#endif
