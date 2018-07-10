/*
    module  : stderr.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef STDERR_X
#define STDERR_C

/**
stderr  :  ->  S
Pushes the standard error stream.
*/
PRIVATE void do_stderr(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(FILE_, stderr);
}
#endif
