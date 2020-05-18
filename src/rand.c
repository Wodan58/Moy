/*
    module  : rand.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef RAND_C
#define RAND_C

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
