/*
    module  : autoput.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef AUTOPUT_X
#define AUTOPUT_C

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
#endif
