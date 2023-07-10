/*
    module  : __symtabmax.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef __SYMTABMAX_C
#define __SYMTABMAX_C

/**
OK 1050  __symtabmax  :  A 	->  I
Pushes value of maximum size of the symbol table.
*/
void __symtabmax_(pEnv env)
{
    Node node;

    node.u.num = sym_max(env->symtab);
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
