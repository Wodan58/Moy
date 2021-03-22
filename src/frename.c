/*
    module  : frename.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FRENAME_C
#define FRENAME_C

/**
frename  :  P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
PRIVATE void do_frename(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("frename");
    STRING("frename");
    STRING2("frename");
    env->stk->next->u.num = !rename(env->stk->next->u.str, env->stk->u.str);
    env->stk->next->op = BOOLEAN_;
    POP(env->stk);
}
#endif
