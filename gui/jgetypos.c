/*
    module  : jgetypos.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETYPOS_C
#define JGETYPOS_C

/**
jgetypos  :  obj  ->  position
Returns the current vertical position of component obj in its parent's
coordinate space.
*/
PRIVATE void do_jgetypos(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getypos(obj);
}
#endif
