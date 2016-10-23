/*
    module  : strftime.c
    version : 1.3
    date    : 09/19/16
*/
#include "interp.h"

/*
strftime  :  T S1  ->  S2
Formats a list T in the format of localtime or gmtime
using string S1 and pushes the result S2.
*/
/* strftime.c */
PRIVATE void strftime_(void)
{
    struct tm t;
    size_t length;
    char *fmt, *result;

    TWOPARAMS("strftime");
    STRING("strftime");
    fmt = stk->u.str;
    POP(stk);
    LIST("strftime");
    decode_time(&t);
    length = INPLINEMAX;
    result = malloc(length);
    strftime(result, length, fmt, &t);
    if (OUTSIDE) {
	stk->u.str = result;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, result);
}
