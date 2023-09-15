/*
    module  : abs.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef ABS_C
#define ABS_C

/**
OK 1480  abs  :  DA	N1  ->  N2
Integer N2 is the absolute value (0,1,2..) of integer N1,
or float N2 is the absolute value (0.0 ..) of float N1.
*/
void abs_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    if (node.op == FLOAT_)
	node.u.dbl = fabs(node.u.dbl);
    else
	node.u.num = llabs(node.u.num);
    lst_push(env->stck, node);
}
#endif
