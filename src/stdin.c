/*
    module  : stdin.c
    version : 1.5
    date    : 07/02/18
*/

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
