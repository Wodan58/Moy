/*
    module  : getenv.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef GETENV_X
#define GETENV_C

#ifdef NEW_RUNTIME
void do_getenv(void)
{
    TRACE;
    stk[-1] = (node_t)getenv((char *)stk[-1]);
}
#else
/**
getenv  :  "variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
PRIVATE void do_getenv(void)
{
#ifndef OLD_RUNTIME
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
#endif
