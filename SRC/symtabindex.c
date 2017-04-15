/*
    module  : symtabindex.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
PRIVATE void do_symtabindex(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, symtabindex);
}
