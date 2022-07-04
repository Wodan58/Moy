/*
    module  : app11.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef APP11_C
#define APP11_C

/**
app11  :  X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
PRIVATE void do_app11(pEnv env)
{
    FOURPARAMS("app11");
    ONEQUOTE("app11");
    do_app1(env);
    env->stk->next = env->stk->next->next; /* delete X */
}
#endif
