/*
    module  : rollupd.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef ROLLUPD_C
#define ROLLUPD_C

/**
OK 1290  rollupd  :  DDDDAAAA	X Y Z W  ->  Z X Y W
As if defined by:   rollupd  ==  [rollup] dip
*/
void rollupd_(pEnv env)
{
    Node first, second, third, fourth;

    PARM(4, ANYTYPE);
    fourth = lst_pop(env->stck);
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    lst_push(env->stck, third);
    lst_push(env->stck, first);
    lst_push(env->stck, second);
    lst_push(env->stck, fourth);
}
#endif
