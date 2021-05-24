/*
    module  : jsetechochar.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETECHOCHAR_C
#define JSETECHOCHAR_C

/**
jsetechochar  :  obj chr  ->
Changes the character chr that is used to echo all user input in the component.
*/
PRIVATE void do_jsetechochar(pEnv env)
{
    int obj, chr;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    CHARACTER(__func__);
    INTEGER2(__func__);
    chr = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setechochar(obj, chr);
}
#endif
