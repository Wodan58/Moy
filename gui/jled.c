/*
    module  : jled.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JLED_C
#define JLED_C

/**
jled  :  obj style color  ->  event
Creates a new led component and returns its event number. The LED's shape could
be round if style=J_ROUND or a rectangle of style=J_RECT. The color could be
one of the predefined colors (e.g. J_RED, J_GREEN).
*/
PRIVATE void do_jled(pEnv env)
{
    int obj, style, color;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    color = env->stk->u.num;
    POP(env->stk);
    style = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_led(obj, style, color);
}
#endif
