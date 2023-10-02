/*
    module  : neql.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef NEQL_C
#define NEQL_C

#include "compare.h"

/**
OK 2260  !=\0neql  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X not equal to Y.  Also supports float.
*/
void neql_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first.u.num = Compare(env, first, second) != 0;
    first.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, first);
}
#endif
