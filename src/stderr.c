/*
    module  : stderr.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef STDERR_X
#define STDERR_C

#ifdef NEW_RUNTIME
void do_stderr(void)
{
    TRACE;
    do_push(stderr);
}
#else
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
#endif
