/*
    module  : jkill.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JKILL_C
#define JKILL_C

/**
jkill  :  ->
Stop the JAPI kernel, or something.
*/
PRIVATE void do_jkill(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    j_kill();
}
#endif
