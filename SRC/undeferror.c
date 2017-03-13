/*
    module  : undeferror.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
undeferror  :  ->  I
Pushes current value of undefined-is-error flag.
*/
PRIVATE void do_undeferror(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, undeferror);
}
