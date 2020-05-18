/*
    module  : getenv.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef GETENV_C
#define GETENV_C

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
    stk->u.str = str;
}
#endif
