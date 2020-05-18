/*
    module  : autoput.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef AUTOPUT_C
#define AUTOPUT_C

/**
autoput  :  ->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
PRIVATE void do_autoput(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, autoput);
}
#endif
