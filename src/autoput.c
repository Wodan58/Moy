/*
    module  : autoput.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef AUTOPUT_C
#define AUTOPUT_C

/**
autoput  :  ->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
PRIVATE void do_autoput(pEnv env)
{
    COMPILE;
    PUSH_NUM(INTEGER_, autoput);
}
#endif
