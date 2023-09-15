/*
    module  : strftime.c
    version : 1.5
    date    : 09/15/23
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
    Node first, second, node;

    PARM(2, STRFTIME);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    decode(first, &t);
    node.u.str = GC_malloc_atomic(INPLINEMAX);
    strftime(node.u.str, INPLINEMAX, second.u.str, &t);
    node.op = STRING_;
    lst_push(env->stck, node);
}
#endif
