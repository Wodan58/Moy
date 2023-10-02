/*
    module  : strftime.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef STRFTIME_C
#define STRFTIME_C

#include "decode.h"

/**
OK 1730  strftime  :  DDA	T S1  ->  S2
Formats a list T in the format of localtime or gmtime
using string S1 and pushes the result S2.
*/
void strftime_(pEnv env)
{
    struct tm t;
    Node first, second;

    PARM(2, STRFTIME);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    decode(first, &t);
    first.u.str = GC_malloc_atomic(INPLINEMAX);
    strftime(first.u.str, INPLINEMAX, second.u.str, &t);
    first.op = STRING_;
    env->stck = pvec_add(env->stck, first);
}
#endif
