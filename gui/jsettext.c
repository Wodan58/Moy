/*
    module  : jsettext.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETTEXT_C
#define JSETTEXT_C

/**
jsettext  :  obj str  ->
Sets the content or the label of the component obj to str.
*/
PRIVATE void do_jsettext(pEnv env)
{
    int obj;
    char *str;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    str = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_settext(obj, str);
}
#endif
