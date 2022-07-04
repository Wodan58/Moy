/*
    module  : echo.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef ECHO_C
#define ECHO_C

/**
echo  :  ->  I
Pushes value of echo flag, I = 0..3.
*/
PRIVATE void do_echo(pEnv env)
{
#ifdef COMPILING
    COMPILE;
    PUSH_NUM(INTEGER_, getechoflag());
#endif
}
#endif
