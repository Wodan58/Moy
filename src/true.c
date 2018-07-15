/*
    module  : true.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef TRUE_X
#define TRUE_C

#ifdef NEW_RUNTIME
void do_true(void)
{
    TRACE;
    do_push(1);
}
#else
/**
true  :  ->  true
Pushes the value true.
*/
PRIVATE void do_true(void)
{
    PUSH(BOOLEAN_, 1);
}
/* true.c */
#endif
#endif
