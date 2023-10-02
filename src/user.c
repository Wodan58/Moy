/*
    module  : user.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef USER_C
#define USER_C

/**
OK 2380  user  :  DA	X  ->  B
Tests whether X is a user-defined symbol.
*/
void user_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op == USR_ ||
		 node.op == USR_STRING_ || node.op == USR_LIST_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
