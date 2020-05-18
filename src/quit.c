/*
    module  : quit.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef QUIT_C
#define QUIT_C

/**
quit  :  ->
Exit from Joy.
*/
PRIVATE void do_quit(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    exit(0);
}
#endif
