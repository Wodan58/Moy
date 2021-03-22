/*
    module  : echo.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef ECHO_C
#define ECHO_C

/**
echo  :  ->  I
Pushes value of echo flag, I = 0..3.
*/
PRIVATE void do_echo(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, getechoflag());
}
#endif
