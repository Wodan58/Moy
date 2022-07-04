/*
    module  : rand.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef RAND_C
#define RAND_C

/**
rand  :  ->  I
I is a random integer.
*/
PRIVATE void do_rand(pEnv env)
{
    COMPILE;
    PUSH_NUM(INTEGER_, rand());
}
#endif
