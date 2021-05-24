/*
    module  : jsethgap.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETHGAP_C
#define JSETHGAP_C

/**
jsethgap  :  obj hgap  ->
Sets the horizontal gap between components to hgap pixels.
*/
PRIVATE void do_jsethgap(pEnv env)
{
    int obj, hgap;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    hgap = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_sethgap(obj, hgap);
}
#endif
