/*
    module  : geql.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef GEQL_C
#define GEQL_C

#include "compare.h"

/**
Q0  OK  2220  >=\0geql  :  DDA  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than or equal to Y.  Also supports float.
*/
void geql_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    if (first.op == SET_ || second.op == SET_)
	first.u.num = !(second.u.set & ~first.u.set);
    else
	first.u.num = Compare(env, first, second) >= 0;
    first.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, first);
}
#endif
