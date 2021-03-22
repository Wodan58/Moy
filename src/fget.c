/*
    module  : fget.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef FGET_C
#define FGET_C

/**
fget  :  S  ->  S F
Reads a factor from stream S and pushes it onto stack.
*/
PRIVATE void do_fget(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fget");
#ifndef NCHECK
    if (env->stk->op != FILE_ || !env->stk->u.fil)
	execerror("file", "fget");
#endif
    redirect(env->stk->u.fil);
    readfactor(env, yylex());
}
#endif
