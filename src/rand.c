/*
    module  : rand.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef RAND_X
#define RAND_C

/**
rand  :  ->  I
I is a random integer.
*/
PRIVATE void do_rand(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, rand());
}
#endif
