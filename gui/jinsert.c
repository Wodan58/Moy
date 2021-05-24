/*
    module  : jinsert.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JINSERT_C
#define JINSERT_C

/**
jinsert  :  obj pos label  ->
Inserts a new item to component obj at position pos with the specified label.
*/
PRIVATE void do_jinsert(pEnv env)
{
    char *label;
    int obj, pos;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    label = env->stk->u.str;
    POP(env->stk);
    pos = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_insert(obj, pos, label);
}
#endif
