/*
    module  : echo.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef ECHO_C
#define ECHO_C

/**
echo  :  ->  I
Pushes value of echo flag, I = 0..3.
*/
PRIVATE void do_echo(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, getechoflag());
}
#endif
