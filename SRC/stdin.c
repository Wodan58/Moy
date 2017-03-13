/*
    module  : stdin.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
stdin  :  ->  S
Pushes the standard input stream.
*/
PRIVATE void do_stdin(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(FILE_, stdin);
}
