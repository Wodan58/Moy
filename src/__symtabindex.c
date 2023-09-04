/*
    module  : __symtabindex.c
    version : 1.3
    date    : 09/04/23
*/
#ifndef __SYMTABINDEX_C
#define __SYMTABINDEX_C

/**
OK 1060  __symtabindex  :  A	->  I
Pushes current size of the symbol table.
*/
void __symtabindex_(pEnv env)
{
    Node node;

    node.u.num = vec_size(env->symtab);
    node.op = INTEGER_;
    lst_push(env->stck, node);
}
#endif
