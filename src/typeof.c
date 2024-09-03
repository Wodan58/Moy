/*
    module  : typeof.c
    version : 1.16
    date    : 08/31/24
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
    env->stck = pvec_pop(env->stck, &node);
    if (node.op == USR_STRING_ || node.op == USR_LIST_)
	node.op = USR_;		/* LCOV_EXCL_LINE */
    node.u.num = node.op;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
