/*
    module  : jenable.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JENABLE_C
#define JENABLE_C

/**
jenable  :  obj  ->
Enables the component obj.
*/
PRIVATE void do_jenable(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_enable(obj);
}
#endif
