/*
    module  : jtranslate.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JTRANSLATE_C
#define JTRANSLATE_C

/**
jtranslate  :  obj x y ->
Moves the origin of drawing operations to (x, y).
*/
PRIVATE void do_jtranslate(pEnv env)
{
    int obj, x, y;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    y = env->stk->u.num;
    POP(env->stk);
    x = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_translate(obj, x, y);
}
#endif
