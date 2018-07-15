/*
    module  : echo.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef ECHO_X
#define ECHO_C

#ifdef NEW_RUNTIME
void do_echo(void)
{
    TRACE;
    do_push(getechoflag());
}
#else
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
#endif
