/*
    module  : jstart.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSTART_C
#define JSTART_C

/**
jstart  :  ->  status
Get in touch with a running JAPI kernel or start a new one.
*/
PRIVATE void do_jstart(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, j_start());
}
#endif
