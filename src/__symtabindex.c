/*
    module  : __symtabindex.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef __SYMTABINDEX_C
#define __SYMTABINDEX_C

/**
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
PRIVATE void do___symtabindex(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
    PUSH(INTEGER_, symtabindex());
#endif
}
#endif
