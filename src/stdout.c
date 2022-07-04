/*
    module  : stdout.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
stdout  :  ->  S
Pushes the standard output stream.
*/
PRIVATE void do_stdout(pEnv env)
{
    COMPILE;
    PUSH_PTR(FILE_, stdout);
}
#endif
