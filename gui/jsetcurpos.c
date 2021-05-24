/*
    module  : jsetcurpos.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETCURPOS_C
#define JSETCURPOS_C

/**
jsetcurpos  :  obj pos  ->
Change the location of the text cursor to the specified position pos.
*/
PRIVATE void do_jsetcurpos(pEnv env)
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
    j_setcurpos(obj, pos);
}
#endif
