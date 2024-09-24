/*
    module  : pred.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef PRED_C
#define PRED_C

/**
Q0  OK  1790  pred  :  DA  M  ->  N
Numeric N is the predecessor of numeric M.
*/
void pred_(pEnv env)
{
    Node node;
#ifdef USE_BIGNUM_ARITHMETIC
    char *first, *second;
#endif

    PARM(1, PREDSUCC);
    node = vec_pop(env->stck);
#ifdef USE_BIGNUM_ARITHMETIC
    if (node.op == BIGNUM_ || node.u.num == -(MAXINT_)) {
        second = num2big(1);
	if (node.u.num == -(MAXINT_)) {
	    first = num2big(-(MAXINT_));
	    node.u.str = num_str_sub(first, second);
	    node.op = BIGNUM_;
	} else
	    node.u.str = num_str_sub(node.u.str, second);
    } else
#endif
    node.u.num--;
    vec_push(env->stck, node);
}
#endif
