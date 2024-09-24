/*
    module  : greater.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef GREATER_C
#define GREATER_C

#include "compare.h"

/**
Q0  OK  2230  >\0greater  :  DDA  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than Y.  Also supports float.
*/
void greater_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    if (first.op == SET_ || second.op == SET_)
	first.u.num = first.u.set != second.u.set &&
		      !(second.u.set & ~first.u.set);
    else
	first.u.num = Compare(env, first, second) > 0;
    first.op = BOOLEAN_;
    vec_push(env->stck, first);
}
#endif
