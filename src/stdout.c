/*
    module  : stdout.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
stdout  :  ->  S
Pushes the standard output stream.
*/
PRIVATE void do_stdout(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(FILE_, stdout);
}
#endif
