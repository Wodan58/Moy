/*
    module  : abort.c
    version : 1.9
    date    : 06/20/22
*/
#ifndef ABORT_C
#define ABORT_C

/**
abort  :  ->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
PRIVATE void do_abort(pEnv env)
{
    COMPILE;
    abortexecution();
}
#endif
