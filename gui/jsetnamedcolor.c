/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETNAMEDCOLOR_C
#define JSETNAMEDCOLOR_C

/**
jsetnamedcolor  :  obj color  ->
Sets the foreground color to a predefined color.
*/
PRIVATE void do_jsetnamedcolor(pEnv env)
{
    int obj, color;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    color = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setnamedcolor(obj, color);
}
#endif
