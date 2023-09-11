/*
    module  : __symtabmax.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef __SYMTABMAX_C
#define __SYMTABMAX_C

/**
OK 1050  __symtabmax  :  A 	->  I
Pushes value of maximum size of the symbol table.
*/
void __symtabmax_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = vec_max(env->symtab);
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
