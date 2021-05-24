/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETFLOWLAYOUT_C
#define JSETFLOWLAYOUT_C

/**
jsetflowlayout  :  obj align  ->
Adds a flowlayout manager to component obj with the specified alignment.
*/
PRIVATE void do_jsetflowlayout(pEnv env)
{
    int obj, align;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    align = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setflowlayout(obj, align);
}
#endif
