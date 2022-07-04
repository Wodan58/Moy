/*
    module  : stderr.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef STDERR_C
#define STDERR_C

/**
stderr  :  ->  S
Pushes the standard error stream.
*/
PRIVATE void do_stderr(pEnv env)
{
    COMPILE;
    PUSH_PTR(FILE_, stderr);
}
#endif
