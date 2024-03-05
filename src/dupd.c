/*
    module  : dupd.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef DUPD_C
#define DUPD_C

/**
Q0  OK  1270  dupd  :  DDAAA  Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
void dupd_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    env->stck = pvec_add(env->stck, first);
    env->stck = pvec_add(env->stck, first);
    env->stck = pvec_add(env->stck, second);
}
#endif
