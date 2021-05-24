/*
    module  : jsetfixlayout.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETFIXLAYOUT_C
#define JSETFIXLAYOUT_C

/**
jsetfixlayout  :  obj  ->
Adds a fixlayout manager to component obj (default layout manager).
*/
PRIVATE void do_jsetfixlayout(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setfixlayout(obj);
}
#endif
