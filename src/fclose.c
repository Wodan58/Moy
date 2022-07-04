/*
    module  : fclose.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef FCLOSE_C
#define FCLOSE_C

/**
fclose  :  S  ->
Stream S is closed and removed from the stack.
*/
PRIVATE void do_fclose(pEnv env)
{
    COMPILE;
    ONEPARAM("fclose");
    FILE("fclose");
    fclose(env->stk->u.fil);
    POP(env->stk);
}
#endif
