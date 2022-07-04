/*
    module  : __symtabmax.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef __SYMTABMAX_C
#define __SYMTABMAX_C

/**
__symtabmax  :  ->  I
Pushes value of maximum size of the symbol table.
*/
PRIVATE void do___symtabmax(pEnv env)
{
#ifdef COMPILING
    COMPILE;
    PUSH_NUM(INTEGER_, symtabmax(env));
#endif
}
#endif
