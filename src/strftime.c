/*
    module  : strftime.c
    version : 1.7
    date    : 07/02/18
*/

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
