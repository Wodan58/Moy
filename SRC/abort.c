/*
    module  : abort.c
    version : 1.1
    date    : 03/12/17
*/
#include "runtime.h"

/*
abort  ->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
PRIVATE void do_abort(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    exit(1);
}
