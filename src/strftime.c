/*
    module  : strftime.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef STRFTIME_C
#define STRFTIME_C

PRIVATE void decode_time(pEnv env, struct tm *t);

#ifdef MKTIME_X
#undef MKTIME_X
#undef MKTIME_C
#endif

#include "mktime.c"

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

#ifndef OLD_RUNTIME
    if (compiling && STRING_1 && LIST_2)
	;
    else
	COMPILE;
#endif
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
