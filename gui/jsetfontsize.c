/*
    module  : jsetfontsize.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETFONTSIZE_C
#define JSETFONTSIZE_C

/**
jsetfontsize  :  obj size  ->
Changes the font to the given size.
*/
PRIVATE void do_jsetfontsize(pEnv env)
{
    int obj, size;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    size = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setfontsize(obj, size);
}
#endif
