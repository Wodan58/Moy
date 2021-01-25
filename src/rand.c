/*
    module  : rand.c
    version : 1.10
    date    : 01/24/21
*/
#ifndef RAND_C
#define RAND_C

int my_rand(void);

/**
rand  :  ->  I
I is a random integer.
*/
PRIVATE void do_rand(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, my_rand());
}
#endif
