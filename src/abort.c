/*
    module  : abort.c
    version : 1.5
    date    : 07/10/18
*/
#ifndef ABORT_X
#define ABORT_C

#ifdef RUNTIME
void do_abort(void)
{
    TRACE;
    exit(0);
}
#else
/**
abort  :  ->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
PRIVATE void do_abort(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    exit(1);
}
#endif
#endif
