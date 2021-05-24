/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETBORDERLAYOUT_C
#define JSETBORDERLAYOUT_C

/**
jsetborderlayout  :  obj  ->
Adds a borderlayout manager to component obj.
*/
PRIVATE void do_jsetborderlayout(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setborderlayout(obj);
}
#endif
