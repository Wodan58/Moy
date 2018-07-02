/*
    module  : getenv.c
    version : 1.5
    date    : 07/02/18
*/

/**
getenv  :  "variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
PRIVATE void do_getenv(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("getenv");
    STRING("getenv");
    if (OUTSIDE)
	stk->u.str = getenv(stk->u.str);
    else
	UNARY(STRING_NEWNODE, getenv(stk->u.str));
}
