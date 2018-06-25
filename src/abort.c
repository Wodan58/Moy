/*
    module  : abort.c
    version : 1.2
    date    : 06/25/18
*/
#include "runtime.h"

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
