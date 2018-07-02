/*
    module  : abort.c
    version : 1.3
    date    : 07/02/18
*/

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
