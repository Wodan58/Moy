/*
    module  : __symtabmax.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef __SYMTABMAX_C
#define __SYMTABMAX_C

/**
__symtabmax  :  ->  I
Pushes value of maximum size of the symbol table.
*/
PRIVATE void do___symtabmax(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, symtabmax(env));
}
#endif
