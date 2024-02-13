/*
    module  : typeof.c
    version : 1.13
    date    : 02/05/24
*/
#ifndef TYPEOF_C
#define TYPEOF_C

/**
OK 3230  typeof  :  DA	X  ->  I
[EXT] Replace X by its type.
*/
void typeof_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    if (node.op == USR_STRING_ || node.op == USR_LIST_)
	node.op = USR_;
    node.u.num = node.op;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
