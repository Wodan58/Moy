/*
    module  : getenv.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef GETENV_X
#define GETENV_C

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
#endif
