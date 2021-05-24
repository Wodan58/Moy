/*
    module  : jpack.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JPACK_C
#define JPACK_C

/**
jpack  :  obj  ->
Resizes component to the minimal size of contained components.
*/
PRIVATE void do_jpack(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_pack(obj);
}
#endif
