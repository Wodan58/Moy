/*
    module  : rolldownd.c
    version : 1.8
    date    : 
*/
#ifndef ROLLDOWND_C
#define ROLLDOWND_C

/**
Q0  OK  1300  rolldownd  :  DDDDAAAA  X Y Z W  ->  Y Z X W
As if defined by:   rolldownd  ==  [rolldown] dip
*/
void rolldownd_(pEnv env)
{
    Node first, second, third, fourth;

    PARM(4, ANYTYPE);
    fourth = vec_pop(env->stck);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    vec_push(env->stck, second);
    vec_push(env->stck, third);
    vec_push(env->stck, first);
    vec_push(env->stck, fourth);
}
#endif
