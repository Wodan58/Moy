/*
    module  : greater.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef GREATER_C
#define GREATER_C

#include "compare.h"

/**
OK 2230  >\0greater  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than Y.  Also supports float.
*/
void greater_(pEnv env)
{
    Node first, second, node;

    PARM(2, ANYTYPE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    if (first.op == SET_ || second.op == SET_)
	node.u.num = first.u.set != second.u.set &&
		     !(second.u.set & ~first.u.set);
    else
	node.u.num = Compare(env, first, second) > 0;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
