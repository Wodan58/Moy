/*
    module  : false.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FALSE_C
#define FALSE_C

/**
false  :  ->  false
Pushes the value false.
*/
PRIVATE void do_false(pEnv env)
{
    PUSH_NUM(BOOLEAN_, 0);
}
/* false.c */
#endif
