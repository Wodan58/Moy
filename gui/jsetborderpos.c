/*
    module  : jsetborderpos.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETBORDERPOS_C
#define JSETBORDERPOS_C

/**
jsetborderpos  :  obj pos  ->
Moves component obj at a certain position. The outer container needs a border
layout manager.
*/
PRIVATE void do_jsetborderpos(pEnv env)
{
    int obj, pos;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    pos = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setborderpos(obj, pos);
}
#endif
