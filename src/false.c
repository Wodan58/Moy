/*
    module  : false.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FALSE_C
#define FALSE_C

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
