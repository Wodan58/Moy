/*
    module  : getenv.c
    version : 1.9
    date    : 07/19/19
*/
#ifndef GETENV_X
#define GETENV_C

#ifdef NEW_RUNTIME
void do_getenv(void)
{
    char *str;

    TRACE;
    if ((str = getenv((char *)stk[-1])) == 0)
	str = "";
    stk[-1] = (node_t)str;
}
#else
/**
getenv  :  "variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
PRIVATE void do_getenv(void)
{
    char *str;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("getenv");
    STRING("getenv");
    if ((str = getenv(stk->u.str)) == 0)
	str = "";
    if (OUTSIDE)
	stk->u.str = str;
    else
	UNARY(STRING_NEWNODE, str);
}
#endif
#endif
