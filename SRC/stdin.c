/*
    module  : stdin.c
    version : 1.3
    date    : 04/09/17
*/
#include "runtime.h"

/*
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
