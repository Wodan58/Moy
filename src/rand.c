/*
    module  : rand.c
    version : 1.6
    date    : 07/02/18
*/

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
