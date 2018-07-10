/*
    module  : argc.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef ARGC_X
#define ARGC_C

#ifdef RUNTIME
void do_argc(void)
{
    TRACE;
    do_push(g_argc);
}
#else
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
#endif
#endif
