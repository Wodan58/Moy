/*
    module  : jgetaction.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETACTION_C
#define JGETACTION_C

/**
jgetaction  :  ->  event
Returns the next event, or 0 of no event available.
*/
PRIVATE void do_jgetaction(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, j_getaction());
}
#endif
