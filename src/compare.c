/*
    module  : compare.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef COMPARE_C
#define COMPARE_C

#include "compare.h"

/**
Q0  OK  2050  compare  :  DDA  A B  ->  I
I (=-1,0,+1) is the comparison of aggregates A and B.
The values correspond to the predicates <=, =, >=.
*/
void compare_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first.u.num = Compare(env, first, second);
    first.op = INTEGER_;
    env->stck = pvec_add(env->stck, first);
}
#endif
