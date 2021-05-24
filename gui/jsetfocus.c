/*
    module  : jsetfocus.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETFOCUS_C
#define JSETFOCUS_C

/**
jsetfocus  :  obj  ->
Directs the input focus to component obj.
*/
PRIVATE void do_jsetfocus(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setfocus(obj);
}
#endif
