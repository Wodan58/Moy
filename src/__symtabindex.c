/*
    module  : __symtabindex.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef __SYMTABINDEX_C
#define __SYMTABINDEX_C

/**
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
PRIVATE void do___symtabindex(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
    PUSH_NUM(INTEGER_, symtabindex(env));
#endif
}
#endif
