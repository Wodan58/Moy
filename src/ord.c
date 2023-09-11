/*
    module  : ord.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef ORD_C
#define ORD_C

/**
OK 1460  ord  :  DA	C  ->  I
Integer I is the Ascii value of character C (or logical or integer).
*/
void ord_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, PREDSUCC);
    node = lst_pop(env->stck);
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
