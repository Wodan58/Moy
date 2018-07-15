/*
    module  : stdout.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef STDOUT_X
#define STDOUT_C

#ifdef NEW_RUNTIME
void do_stdout(void)
{
    TRACE;
    do_push((node_t)stdout);
}
#else
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
#endif
