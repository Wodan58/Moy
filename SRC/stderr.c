/*
    module  : stderr.c
    version : 1.3
    date    : 04/09/17
*/
#include "runtime.h"

/*
stderr  :  ->  S
Pushes the standard error stream.
*/
PRIVATE void do_stderr(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(FILE_);
    COMPILE;
#endif
    PUSH(FILE_, stderr);
}
