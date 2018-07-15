/*
    module  : strftime.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef STRFTIME_X
#define STRFTIME_C

PRIVATE void decode_time(struct tm *t);

#ifndef MKTIME_C
#undef MKTIME_X
#include "mktime.c"
#define MKTIME_X
#endif

#ifdef NEW_RUNTIME
void do_strftime(void)
{
    struct tm t;
    size_t length;
    char *fmt, *result;

    TRACE;
    fmt = (char *)do_pop();
    decode_time(&t);
    length = INPLINEMAX;
    result = ck_malloc_sec(length);
    strftime(result, length, fmt, &t);
    stk[-1] = (node_t)result;
}
#else
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
#endif
