/*
    module  : echo.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef ECHO_X
#define ECHO_C

/**
echo  :  ->  I
Pushes value of echo flag, I = 0..3.
*/
PRIVATE void do_echo(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, getechoflag());
}
#endif
