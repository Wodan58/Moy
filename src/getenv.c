/*
    module  : getenv.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef GETENV_C
#define GETENV_C

/**
getenv  :  "variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
PRIVATE void do_getenv(pEnv env)
{
    char *str;

    COMPILE;
    ONEPARAM("getenv");
    STRING("getenv");
    if ((str = getenv(env->stk->u.str)) == 0)
	str = "";
    UNARY(STRING_NEWNODE, str);
}
#endif
