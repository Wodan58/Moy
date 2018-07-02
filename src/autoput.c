/*
    module  : autoput.c
    version : 1.6
    date    : 07/02/18
*/

/**
autoput  :  ->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
PRIVATE void do_autoput(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, autoput);
}
