/*
    module  : jnextaction.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JNEXTACTION_C
#define JNEXTACTION_C

/**
jnextaction  :  ->  event
Waits for the next event.
*/
PRIVATE void do_jnextaction(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, j_nextaction());
}
#endif
