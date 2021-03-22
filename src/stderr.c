/*
    module  : stderr.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef STDERR_C
#define STDERR_C

/**
stderr  :  ->  S
Pushes the standard error stream.
*/
PRIVATE void do_stderr(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_PTR(FILE_, stderr);
}
#endif
