/*
    module  : rand.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef RAND_X
#define RAND_C

#ifdef NEW_VERSION
void do_rand(void)
{
    TRACE;
    do_push(rand());
}
#else
/**
rand  :  ->  I
I is a random integer.
*/
PRIVATE void do_rand(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, rand());
}
#endif
#endif
