/*
    module  : stdin.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef STDIN_C
#define STDIN_C

/**
stdin  :  ->  S
Pushes the standard input stream.
*/
PRIVATE void do_stdin(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(FILE_, stdin);
}
#endif
