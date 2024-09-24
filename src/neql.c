/*
    module  : neql.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef NEQL_C
#define NEQL_C

#include "compare.h"

/**
Q0  OK  2260  !=\0neql  :  DDA  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X not equal to Y.  Also supports float.
*/
void neql_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first.u.num = Compare(env, first, second) != 0;
    first.op = BOOLEAN_;
    vec_push(env->stck, first);
}
#endif
