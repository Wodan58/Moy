/*
    module  : jsetalign.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETALIGN_C
#define JSETALIGN_C

/**
jsetalign  :  obj align  ->
Sets the alignment in component obj to align. Needs a flowlayout manager.
*/
PRIVATE void do_jsetalign(pEnv env)
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
    j_setalign(obj, align);
}
#endif
