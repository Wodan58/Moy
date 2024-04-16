/*
    module  : succ.c
    version : 1.8
    date    : 04/11/24
*/
#ifndef SUCC_C
#define SUCC_C

/**
Q0  OK  1800  succ  :  DA  M  ->  N
Numeric N is the successor of numeric M.
*/
void succ_(pEnv env)
{
    Node node;
#ifdef USE_BIGNUM_ARITHMETIC
    char *first, *second;
#endif

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
#ifdef USE_BIGNUM_ARITHMETIC
    if (node.op == BIGNUM_ || node.u.num == MAXINT_) {
	second = num2big(1);
	if (node.u.num == MAXINT_) {
	    first = num2big(MAXINT_);
	    node.u.str = num_str_add(first, second);
	    node.op = BIGNUM_;
	} else
	    node.u.str = num_str_add(node.u.str, second);
    } else
#endif
    node.u.num++;
    env->stck = pvec_add(env->stck, node);
}
#endif
