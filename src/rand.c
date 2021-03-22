/*
    module  : rand.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef RAND_C
#define RAND_C

int my_rand(void);

/**
rand  :  ->  I
I is a random integer.
*/
PRIVATE void do_rand(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, my_rand());
}
#endif
