/*
    module  : leql.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef LEQL_C
#define LEQL_C

#include "compare.h"

/**
OK 2240  <=\0leql  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X less than or equal to Y.  Also supports float.
*/
void leql_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    if (first.op == SET_ || second.op == SET_)
	first.u.num = !(first.u.set & ~second.u.set);
    else
	first.u.num = Compare(env, first, second) <= 0;
    first.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, first);
}
#endif
