/*
    module  : getenv.c
    version : 1.11
    date    : 03/15/21
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

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("getenv");
    STRING("getenv");
    if ((str = getenv(env->stk->u.str)) == 0)
	str = "";
    env->stk->u.str = str;
}
#endif
