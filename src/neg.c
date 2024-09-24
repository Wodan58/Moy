/*
    module  : neg.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef NEG_C
#define NEG_C

/**
Q0  OK  1450  neg  :  DA  I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
void neg_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    if (node.op == FLOAT_)
	node.u.dbl = -node.u.dbl;
    else
	node.u.num = -node.u.num;
    vec_push(env->stck, node);
}
#endif
