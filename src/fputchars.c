/*
    module  : fputchars.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FPUTCHARS_C
#define FPUTCHARS_C

/**
fputchars  :  S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
PRIVATE void do_fputchars(pEnv env)
{
    char *str;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fputchars");
#ifndef NCHECK
    if (env->stk->next->op != FILE_ || !env->stk->next->u.fil)
	execerror("file", "fputchars");
#endif
    str = env->stk->u.str;
    POP(env->stk);
    fprintf(env->stk->u.fil, "%s", str);
}
#endif
