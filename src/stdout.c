/*
    module  : stdout.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef STDOUT_X
#define STDOUT_C

/**
stdout  :  ->  S
Pushes the standard output stream.
*/
PRIVATE void do_stdout(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(FILE_, stdout);
}
#endif
