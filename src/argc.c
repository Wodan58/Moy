/*
    module  : argc.c
    version : 1.6
    date    : 07/02/18
*/

/**
argc  :  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
PRIVATE void do_argc(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, g_argc);
}
