/*
    module  : strftime.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef STRFTIME_C
#define STRFTIME_C

#include "decode.h"

/**
strftime  :  T S1  ->  S2
Formats a list T in the format of localtime or gmtime
using string S1 and pushes the result S2.
*/
PRIVATE void do_strftime(pEnv env)
{
    struct tm t;
    size_t length;
    char *fmt, *result;

    TWOPARAMS("strftime");
    STRING("strftime");
    fmt = env->stk->u.str;
    POP(env->stk);
    LIST("strftime");
    decode_time(env, &t);
    length = INPLINEMAX;
    result = GC_malloc_atomic(length);
    strftime(result, length, fmt, &t);
    PUSH_PTR(STRING_, result);
}
#endif
