/*
    module  : argc.c
    version : 1.7
    date    : 07/05/18
*/
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
