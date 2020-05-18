/*
    module  : __dump.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef __DUMP_C
#define __DUMP_C

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
