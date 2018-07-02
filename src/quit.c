/*
    module  : quit.c
    version : 1.4
    date    : 07/02/18
*/

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
