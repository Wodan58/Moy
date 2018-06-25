/*
    module  : getenv.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
getenv  :  "variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
PRIVATE void do_getenv(void)
{
#ifndef NCHECK
    COMPILE;
    ONEPARAM("getenv");
    STRING("getenv");
#endif
    if (OUTSIDE)
	stk->u.str = getenv(stk->u.str);
    else
	UNARY(STRING_NEWNODE, getenv(stk->u.str));
}
