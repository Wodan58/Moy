/*
    module  : typeof.c
    version : 1.2
    date    : 08/23/23
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
    node = lst_pop(env->stck);
    node.u.num = node.op;
    node.op = INTEGER_;
    lst_push(env->stck, node);    
}
#endif
