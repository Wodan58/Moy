/*
    module  : stdout.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
stdout  :  ->  S
Pushes the standard output stream.
*/
PRIVATE void do_stdout(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_PTR(FILE_, stdout);
}
#endif
