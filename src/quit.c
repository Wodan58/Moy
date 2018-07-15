/*
    module  : quit.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef QUIT_X
#define QUIT_C

#ifdef NEW_RUNTIME
void do_quit(void)
{
    TRACE;
    exit(0);
}
#else
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
#endif
