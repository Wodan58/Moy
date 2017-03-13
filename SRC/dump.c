/*
    module  : dump.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
__dump  :  ->  [..]
debugging only: pushes the dump as a list.
*/
PRIVATE void do_dump(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
