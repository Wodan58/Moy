/*
    module  : quit.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef QUIT_C
#define QUIT_C

/**
quit  :  ->
Exit from Joy.
*/
PRIVATE void do_quit(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    exit(0);
}
#endif
