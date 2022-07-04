/*
    module  : argc.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef ARGC_C
#define ARGC_C

/**
argc  :  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
PRIVATE void do_argc(pEnv env)
{
    COMPILE;
    PUSH_NUM(INTEGER_, g_argc);
}
#endif
