/*
    module  : __dump.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef __DUMP_C
#define __DUMP_C

/**
__dump  :  ->  [..]
debugging only: pushes the dump as a list.
*/
PRIVATE void do___dump(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_PTR(LIST_, 0);
}
#endif
