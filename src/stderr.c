/*
    module  : stderr.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef STDERR_C
#define STDERR_C

/**
stderr  :  ->  S
Pushes the standard error stream.
*/
PRIVATE void do_stderr(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(FILE_, stderr);
}
#endif
