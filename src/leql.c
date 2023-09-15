/*
    module  : leql.c
    version : 1.5
    date    : 09/15/23
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
    Node first, second, node;

    PARM(2, ANYTYPE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    if (first.op == SET_ || second.op == SET_)
	node.u.num = !(first.u.set & ~second.u.set);
    else
	node.u.num = Compare(env, first, second) <= 0;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
