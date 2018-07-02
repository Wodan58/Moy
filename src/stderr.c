/*
    module  : stderr.c
    version : 1.5
    date    : 07/02/18
*/

/**
stderr  :  ->  S
Pushes the standard error stream.
*/
PRIVATE void do_stderr(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(FILE_, stderr);
}
