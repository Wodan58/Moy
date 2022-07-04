/*
    module  : true.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef TRUE_C
#define TRUE_C

/**
true  :  ->  true
Pushes the value true.
*/
PRIVATE void do_true(pEnv env)
{
    PUSH_NUM(BOOLEAN_, 1);
}
/* true.c */
#endif
