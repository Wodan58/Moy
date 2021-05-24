/*
    module  : jsetfontstyle.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETFONTSTYLE_C
#define JSETFONTSTYLE_C

/**
jsetfontstyle  :  obj style  ->
Changes the font to the given style.
*/
PRIVATE void do_jsetfontstyle(pEnv env)
{
    int obj, style;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    style = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setfontstyle(obj, style);
}
#endif
