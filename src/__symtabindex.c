/*
    module  : __symtabindex.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef __SYMTABINDEX_C
#define __SYMTABINDEX_C

/**
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
PRIVATE void do___symtabindex(pEnv env)
{
#ifdef COMPILING
    COMPILE;
    PUSH_NUM(INTEGER_, symtabindex(env));
#endif
}
#endif
