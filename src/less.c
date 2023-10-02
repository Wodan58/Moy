/*
    module  : less.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef LESS_C
#define LESS_C

#include "compare.h"

/**
OK 2250  <\0less  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X less than Y.  Also supports float.
*/
void less_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    if (first.op == SET_ || second.op == SET_)
	first.u.num = first.u.set != second.u.set &&
		      !(first.u.set & ~second.u.set);
    else
	first.u.num = Compare(env, first, second) < 0;
    first.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, first);
}
#endif
