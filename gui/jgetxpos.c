/*
    module  : jgetxpos.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETXPOS_C
#define JGETXPOS_C

/**
jgetxpos  :  obj  ->  position
Returns the horizontal position of component obj in its parent's coordinate
space.
*/
PRIVATE void do_jgetxpos(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getxpos(obj);
}
#endif
