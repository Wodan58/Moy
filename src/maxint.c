/*
    module  : maxint.c
    version : 1.7
    date    : 07/02/18
*/

/**
maxint  :  ->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
PRIVATE void do_maxint(void)
{
    PUSH(INTEGER_, MAXINT_);
}
