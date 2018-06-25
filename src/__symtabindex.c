/*
    module  : __symtabindex.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
PRIVATE void do___symtabindex(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, symtabindex);
}
