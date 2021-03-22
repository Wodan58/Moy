/*
    module  : abort.c
    version : 1.8
    date    : 03/15/21
*/
#ifndef ABORT_C
#define ABORT_C

/**
abort  :  ->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
PRIVATE void do_abort(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    exit(1);
}
#endif
