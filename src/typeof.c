/*
    module  : typeof.c
    version : 1.3
    date    : 08/26/23
*/
#ifndef TYPEOF_C
#define TYPEOF_C

/**
OK 2323  typeof  :  DA	X  ->  I
Replace X by its type.
*/
void typeof_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    node.u.num = node.op;
    node.op = INTEGER_;
    lst_push(env->stck, node);    
}
#endif
