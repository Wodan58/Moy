/*
    module  : app11.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef APP11_C
#define APP11_C

/**
app11  :  X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
PRIVATE void do_app11(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS("app11");
    ONEQUOTE("app11");
    do_app1(env);
    env->stk->next = env->stk->next->next;
}
#endif
