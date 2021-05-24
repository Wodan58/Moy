/*
    module  : jquit.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JQUIT_C
#define JQUIT_C

/**
jquit  :  ->
Cancels the connection to the JAPI Kernel.
*/
PRIVATE void do_jquit(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    j_quit();
}
#endif
