/*
    module  : fget.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef FGET_C
#define FGET_C

/**
fget  :  S  ->  S F
Reads a factor from stream S and pushes it onto stack.
*/
PRIVATE void do_fget(pEnv env)
{
    FILE *fp;
    int stdin_dup;

    COMPILE;
    ONEPARAM("fget");
    FILE("fget");
    fp = env->stk->u.fil;
    if ((stdin_dup = dup(0)) != -1)
	dup2(fileno(fp), 0);
    readfactor(env, yylex(env));
    if (stdin_dup != -1) {
	dup2(stdin_dup, 0);
	close(stdin_dup);
    }
}
#endif
