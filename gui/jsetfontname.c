/*
    module  : jsetfontname.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETFONTNAME_C
#define JSETFONTNAME_C

/**
jsetfontname  :  obj name  ->
Changes the font to the given name.
*/
PRIVATE void do_jsetfontname(pEnv env)
{
    int obj, name;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    name = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setfontname(obj, name);
}
#endif
