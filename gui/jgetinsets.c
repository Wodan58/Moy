/*
    module  : jgetinsets.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETINSETS_C
#define JGETINSETS_C

/**
jgetinsets  :  obj side  ->  height
Returns the width of the specified inset. Side can take the following values:
J_TOP: returns the height of the top inset; J_BOTTOM: returns the height of the
bottom inset; J_LEFT: returns the width of the left inset; J_RIGHT: returns the
width of the right inset.
*/
PRIVATE void do_jgetinsets(pEnv env)
{
    int obj, side;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    side = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_getinsets(obj, side);
}
#endif
