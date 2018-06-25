/*
    module  : stdin.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
stdin  :  ->  S
Pushes the standard input stream.
*/
PRIVATE void do_stdin(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(FILE_);
    COMPILE;
#endif
    PUSH(FILE_, stdin);
}
