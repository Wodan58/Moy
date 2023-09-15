/*
    module  : rolldownd.c
    version : 1.5
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
    fourth = lst_pop(env->stck);
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    lst_push(env->stck, second);
    lst_push(env->stck, third);
    lst_push(env->stck, first);
    lst_push(env->stck, fourth);
}
#endif
