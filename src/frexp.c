/*
    module  : frexp.c
    version : 1.8
    date    : 03/21/24
*/
#ifndef FREXP_C
#define FREXP_C

/**
Q0  OK  1580  frexp  :  DAA  F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
void frexp_(pEnv env)
{
    int exp;
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    if (node.op != FLOAT_) {
	node.u.dbl = node.u.num;
	node.op = FLOAT_;
    }
    node.u.dbl = frexp(node.u.dbl, &exp);
    env->stck = pvec_add(env->stck, node);
    node.u.num = exp;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
