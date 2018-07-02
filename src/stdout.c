/*
    module  : stdout.c
    version : 1.5
    date    : 07/02/18
*/

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
