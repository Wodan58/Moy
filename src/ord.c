/*
    module  : ord.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef ORD_C
#define ORD_C

/**
OK 1460  ord  :  DA	C  ->  I
Integer I is the Ascii value of character C (or logical or integer).
*/
void ord_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = vec_pop(env->stck);
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
