/*
    module  : jrandom.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JRANDOM_C
#define JRANDOM_C

/**
jrandom  :  ->  number
Generates a pseudo randon number. The returned value will be in the range 0 to
2147483647 (2 ^ 31 - 1).
*/
PRIVATE void do_jrandom(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, j_random());
}
#endif
