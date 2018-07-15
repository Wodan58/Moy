/*
    module  : stdin.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef STDIN_X
#define STDIN_C

#ifdef NEW_RUNTIME
void do_stdin(void)
{
    TRACE;
    do_push(stdin);
}
#else
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
#endif
