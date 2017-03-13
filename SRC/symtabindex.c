/*
    module  : symtabindex.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
PRIVATE void do_symtabindex(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, symtabindex);
}
