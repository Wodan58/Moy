/*
    module  : __dump.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef __DUMP_X
#define __DUMP_C

#ifdef NEW_RUNTIME
void do___dump(void)
{
    TRACE;
    do_push(0);
}
#else
/**
__dump  :  ->  [..]
debugging only: pushes the dump as a list.
*/
PRIVATE void do___dump(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
#endif
#endif
