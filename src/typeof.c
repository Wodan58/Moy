/*
    module  : typeof.c
    version : 1.17
    date    : 09/17/24
*/
#ifndef TYPEOF_C
#define TYPEOF_C

/**
Q0  OK  3220  typeof  :  DA  X  ->  I
[EXT] Replace X by its type.
*/
void typeof_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    if (node.op == USR_STRING_ || node.op == USR_LIST_)
	node.op = USR_;		/* LCOV_EXCL_LINE */
    node.u.num = node.op;
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
