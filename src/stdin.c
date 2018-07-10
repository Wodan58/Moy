/*
    module  : stdin.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef STDIN_X
#define STDIN_C

/**
stdin  :  ->  S
Pushes the standard input stream.
*/
PRIVATE void do_stdin(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(FILE_, stdin);
}
#endif
