/*
    module  : jsync.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSYNC_C
#define JSYNC_C

/**
jsync  :  ->
Synchronizes the application with the JAPI kernel.
*/
PRIVATE void do_jsync(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    j_sync();
}
#endif
