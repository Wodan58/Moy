/*
    module  : dump.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
__dump  :  ->  [..]
debugging only: pushes the dump as a list.
*/
PRIVATE void do_dump(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(LIST_);
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
