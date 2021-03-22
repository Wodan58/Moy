/*
    module  : fremove.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FREMOVE_C
#define FREMOVE_C

/**
fremove  :  P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
PRIVATE void do_fremove(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fremove");
    STRING("fremove");
    env->stk->next->u.num = !remove(env->stk->u.str);
    env->stk->next->op = BOOLEAN_;
    POP(env->stk);
}
#endif
