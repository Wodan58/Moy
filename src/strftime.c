/*
    module  : strftime.c
    version : 1.6
    date    : 06/25/18
*/
#include "runtime.h"

PRIVATE void decode_time(struct tm *t);

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

#ifndef NCHECK
    if (optimizing) {
	del_history(1);
	chg_history(STRING_);
    }
    if (optimizing && STRING_1 && LIST_2)
	;
    else
	COMPILE;
    TWOPARAMS("strftime");
    STRING("strftime");
#endif
    fmt = stk->u.str;
    POP(stk);
#ifndef NCHECK
    LIST("strftime");
#endif
    decode_time(&t);
    length = INPLINEMAX;
    result = GC_malloc_atomic(length);
    strftime(result, length, fmt, &t);
    PUSH(STRING_, result);
}
