/*
    module  : x.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef X_C
#define X_C

/**
x  :  [P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
PRIVATE void do_x(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("x");
    ONEQUOTE("x");
    exeterm(env, env->stk->u.lis);
}
#endif
