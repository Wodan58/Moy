/*
    module  : app11.c
    version : 1.12
    date    : 07/25/22
*/
#ifndef APP11_C
#define APP11_C

/**
app11  :  X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
PRIVATE void do_app11(pEnv env)
{
    THREEPARAMS("app11");
    ONEQUOTE("app11");
    do_app1(env);
    if (env->stk->next)
	env->stk->next = env->stk->next->next; /* delete X */
}
#endif
