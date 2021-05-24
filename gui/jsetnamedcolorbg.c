/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETNAMEDCOLORBG_C
#define JSETNAMEDCOLORBG_C

/**
jsetnamedcolorbg  :  obj color  ->
Sets the background color to a predefined color.
*/
PRIVATE void do_jsetnamedcolorbg(pEnv env)
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
    j_setnamedcolorbg(obj, color);
}
#endif
