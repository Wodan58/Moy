/*
    module  : stdin.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef STDIN_C
#define STDIN_C

/**
stdin  :  ->  S
Pushes the standard input stream.
*/
PRIVATE void do_stdin(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_PTR(FILE_, stdin);
}
#endif
