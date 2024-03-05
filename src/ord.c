/*
    module  : ord.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef ORD_C
#define ORD_C

/**
Q0  OK  1460  ord  :  DA  C  ->  I
Integer I is the Ascii value of character C (or logical or integer).
*/
void ord_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
