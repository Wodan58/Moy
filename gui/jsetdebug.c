/*
    module  : jsetdebug.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETDEBUG_C
#define JSETDEBUG_C

/**
jsetdebug  :  level  ->
Sets the debuglevel to level.
*/
PRIVATE void do_jsetdebug(pEnv env)
{
    int level;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    level = env->stk->u.num;
    POP(env->stk);
    j_setdebug(level);
}
#endif
