/*
    module  : true.c
    version : 1.10
    date    : 03/15/21
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
