/*
    module  : __dump.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef __DUMP_X
#define __DUMP_C

/**
__dump  :  ->  [..]
debugging only: pushes the dump as a list.
*/
PRIVATE void do___dump(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
#endif
