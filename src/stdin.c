/*
    module  : stdin.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef STDIN_C
#define STDIN_C

/**
stdin  :  ->  S
Pushes the standard input stream.
*/
PRIVATE void do_stdin(pEnv env)
{
    COMPILE;
    PUSH_PTR(FILE_, stdin);
}
#endif
