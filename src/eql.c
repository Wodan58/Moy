/*
    module  : eql.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef EQL_C
#define EQL_C

#include "compare.h"

/**
Q0  OK  2270  =\0equals  :  DDA  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X equal to Y.  Also supports float.
*/
void eql_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first.u.num = Compare(env, first, second) == 0;
    first.op = BOOLEAN_;
    vec_push(env->stck, first);
}
#endif
