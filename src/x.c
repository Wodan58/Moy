/*
    module  : x.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef X_C
#define X_C

/**
x  :  [P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
PRIVATE void do_x(pEnv env)
{
    ONEPARAM("x");
    ONEQUOTE("x");
    exeterm(env, env->stk->u.lis);
}
#endif
