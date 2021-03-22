/*
    module  : fclose.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FCLOSE_C
#define FCLOSE_C

/**
fclose  :  S  ->
Stream S is closed and removed from the stack.
*/
PRIVATE void do_fclose(pEnv env)
{
    FILE *fp;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fclose");
    FILE("fclose");
    if ((fp = env->stk->u.fil) != 0)
	fclose(fp);
    POP(env->stk);
}
#endif
