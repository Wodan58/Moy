/*
    module  : abort.c
    version : 1.4
    date    : 07/05/18
*/
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
