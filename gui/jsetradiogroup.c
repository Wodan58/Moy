/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETRADIOGROUP_C
#define JSETRADIOGROUP_C

/**
jsetradiogroup  :  rbutton rgroup  ->
Sets radiobutton rbutton group to be the specified radiogroup rgroup. If the
radiobutton is already in a different radiogroup, it is first taken out of that
group.
*/
PRIVATE void do_jsetradiogroup(pEnv env)
{
    int rbutton, rgroup;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    rgroup = env->stk->u.num;
    POP(env->stk);
    rbutton = env->stk->u.num;
    POP(env->stk);
    j_setradiogroup(rbutton, rgroup);
}
#endif
