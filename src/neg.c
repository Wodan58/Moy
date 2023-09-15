/*
    module  : neg.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef NEG_C
#define NEG_C

/**
OK 1450  neg  :  DA	I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
void neg_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    if (node.op == FLOAT_)
	node.u.dbl = -node.u.dbl;
    else
	node.u.num = -node.u.num;
    lst_push(env->stck, node);
}
#endif
