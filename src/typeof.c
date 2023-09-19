/*
    module  : typeof.c
    version : 1.7
    date    : 09/19/23
*/
#ifndef TYPEOF_C
#define TYPEOF_C

/**
OK 3250  typeof  :  DA	X  ->  I
[EXT] Replace X by its type.
*/
void typeof_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    if (node.op == USR_STRING_ || node.op == USR_LIST_)
	node.op = USR_;
    node.u.num = node.op;
    node.op = INTEGER_;
    lst_push(env->stck, node);    
}
#endif
