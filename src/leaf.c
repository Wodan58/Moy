/*
    module  : leaf.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef LEAF_C
#define LEAF_C

/**
OK 2370  leaf  :  DA	X  ->  B
Tests whether X is not a list.
*/
void leaf_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op != LIST_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
