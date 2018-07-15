/*
    module  : abort.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef ABORT_X
#define ABORT_C

#ifdef NEW_RUNTIME
void do_abort(void)
{
    TRACE;
    exit(1);
}
#else
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
#endif
