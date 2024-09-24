/*
    module  : __symtabmax.c
    version : 1.8
    date    : 09/17/24
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
    vec_push(env->stck, node);
}
#endif
