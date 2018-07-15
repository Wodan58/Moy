/*
    module  : autoput.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef AUTOPUT_X
#define AUTOPUT_C

#ifdef NEW_RUNTIME
void do_autoput(void)
{
    TRACE;
    do_push(autoput);
}
#else
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
#endif
