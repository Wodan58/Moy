/*
    module  : strftime.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef STRFTIME_C
#define STRFTIME_C

PRIVATE void decode_time(struct tm *t);

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
PRIVATE void do_strftime(void)
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
    fmt = stk->u.str;
    POP(stk);
    LIST("strftime");
    decode_time(&t);
    length = INPLINEMAX;
    result = ck_malloc_sec(length);
    strftime(result, length, fmt, &t);
    PUSH(STRING_, result);
}
#endif
