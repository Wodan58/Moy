/*
    module  : autoput.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef AUTOPUT_C
#define AUTOPUT_C

/**
autoput  :  ->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
PRIVATE void do_autoput(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, autoput);
}
#endif
