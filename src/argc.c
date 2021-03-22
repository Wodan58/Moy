/*
    module  : argc.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef ARGC_C
#define ARGC_C

/**
argc  :  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
PRIVATE void do_argc(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, g_argc);
}
#endif
