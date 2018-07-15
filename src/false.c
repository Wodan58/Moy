/*
    module  : false.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FALSE_X
#define FALSE_C

#ifdef NEW_RUNTIME
void do_false(void)
{
    TRACE;
    do_push(0);
}
#else
/**
false  :  ->  false
Pushes the value false.
*/
PRIVATE void do_false(void)
{
    PUSH(BOOLEAN_, 0);
}
/* false.c */
#endif
#endif
