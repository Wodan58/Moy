/*
    module  : echo.c
    version : 1.6
    date    : 07/02/18
*/

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
