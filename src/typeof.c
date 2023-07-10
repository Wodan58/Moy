/*
    module  : typeof.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef TYPEOF_C
#define TYPEOF_C

/**
OK 3250  typeof  :  DA	X  ->  I
Replace X by its type.
*/
void typeof_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    node.u.num = node.op;
    node.op = INTEGER_;
    vec_push(env->stck, node);    
}
#endif
