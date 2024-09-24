/*
    module  : leql.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef LEQL_C
#define LEQL_C

#include "compare.h"

/**
Q0  OK  2240  <=\0leql  :  DDA  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X less than or equal to Y.  Also supports float.
*/
void leql_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    if (first.op == SET_ || second.op == SET_)
	first.u.num = !(first.u.set & ~second.u.set);
    else
	first.u.num = Compare(env, first, second) <= 0;
    first.op = BOOLEAN_;
    vec_push(env->stck, first);
}
#endif
