/*
    module  : quit.c
    version : 1.5
    date    : 07/05/18
*/
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
