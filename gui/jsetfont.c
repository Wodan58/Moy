/*
    module  : jsetfont.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETFONT_C
#define JSETFONT_C

/**
jsetfont  :  obj name style size  ->
Changes the font to the given characteristics name, style, and size.
*/
PRIVATE void do_jsetfont(pEnv env)
{
    int obj, name, style, size;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FOURPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    size = env->stk->u.num;
    POP(env->stk);
    style = env->stk->u.num;
    POP(env->stk);
    name = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setfont(obj, name, style, size);
}
#endif
