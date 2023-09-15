/*
    module  : frexp.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef FREXP_C
#define FREXP_C

/**
OK 1580  frexp  :  DAA	F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
PRIVATE void frexp_(pEnv env)
{
    int exp;
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    if (node.op != FLOAT_) {
	node.u.dbl = node.u.num;
	node.op = FLOAT_;
    }
    node.u.dbl = frexp(node.u.dbl, &exp);
    lst_push(env->stck, node);
    node.u.num = exp;
    node.op = INTEGER_;
    lst_push(env->stck, node);
}
#endif
