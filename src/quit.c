/*
    module  : quit.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef QUIT_X
#define QUIT_C

#ifdef RUNTIME
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
#ifndef NCHECK
    COMPILE;
#endif
    exit(0);
}
#endif
#endif
