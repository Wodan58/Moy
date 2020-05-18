/*
    module  : argc.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef ARGC_C
#define ARGC_C

/**
argc  :  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
PRIVATE void do_argc(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, g_argc);
}
#endif
