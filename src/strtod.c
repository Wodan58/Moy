/*
    module  : strtod.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef STRTOD_C
#define STRTOD_C

/**
strtod  :  S  ->  R
String S is converted to the float R.
*/
PRIVATE void do_strtod(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && STRING_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("strtod");
    STRING("strtod");
    env->stk->u.num = strtod(env->stk->u.str, 0);
    env->stk->op = FLOAT_;
}
#endif
