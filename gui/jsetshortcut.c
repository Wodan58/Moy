/*
    module  : jsetshortcut.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETSHORTCUT_C
#define JSETSHORTCUT_C

/**
jsetshortcut  :  obj chr  ->
Changed the shortcut chr of the component.
*/
PRIVATE void do_jsetshortcut(pEnv env)
{
    int obj, chr;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    chr = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setshortcut(obj, chr);
}
#endif
