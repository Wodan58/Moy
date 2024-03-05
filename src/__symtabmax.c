/*
    module  : __symtabmax.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef __SYMTABMAX_C
#define __SYMTABMAX_C

/**
Q0  OK  1050  __symtabmax  :  A  ->  I
Pushes value of maximum size of the symbol table.
*/
void __symtabmax_(pEnv env)
{
    Node node;

    node.u.num = vec_max(env->symtab);
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
