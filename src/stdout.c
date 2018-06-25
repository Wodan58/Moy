/*
    module  : stdout.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
stdout  :  ->  S
Pushes the standard output stream.
*/
PRIVATE void do_stdout(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(FILE_);
    COMPILE;
#endif
    PUSH(FILE_, stdout);
}
