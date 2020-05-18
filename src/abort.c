/*
    module  : abort.c
    version : 1.7
    date    : 03/28/20
*/
#ifndef ABORT_C
#define ABORT_C

/**
abort  :  ->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
PRIVATE void do_abort(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    exit(1);
}
#endif
