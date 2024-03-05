/*
    module  : divide.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef DIVIDE_C
#define DIVIDE_C

/**
Q0  OK  1410  /\0divide  :  DDA  I J  ->  K
Integer K is the (rounded) ratio of integers I and J.  Also supports float.
*/
void divide_(pEnv env)
{
#ifdef USE_BIGNUM_ARITHMETIC
    char *str;
    double dbl;
    int64_t num;
    int leng, leng1, leng2;
#endif
    Node first, second;

    PARM(2, DIVIDE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    switch (first.op) {
#ifdef USE_BIGNUM_ARITHMETIC
    case BIGNUM_:
	leng1 = strlen(first.u.str);
	switch (second.op) {
	case BIGNUM_:
	    leng2 = strlen(second.u.str);
	    leng = max(leng1, leng2) + env->scale;
	    leng = max(leng, 10);
	    str = GC_malloc_atomic(leng + 1);
	    if (num_div(first.u.str, second.u.str, str, leng))
		first.u.str = str;
	    break;

	case FLOAT_:
	    second.u.str = dbl2big(second.u.dbl);
	    leng2 = strlen(second.u.str);
	    leng = max(leng1, leng2) + env->scale;
	    leng = max(leng, 10);
	    str = GC_malloc_atomic(leng + 1);
	    if (num_div(first.u.str, second.u.str, str, leng))
		first.u.str = str;
	    break;

	default:
	    second.u.str = num2big(second.u.num);
	    leng2 = strlen(second.u.str);
	    leng = max(leng1, leng2) + env->scale;
	    leng = max(leng, 10);
	    str = GC_malloc_atomic(leng + 1);
	    if (num_div(first.u.str, second.u.str, str, leng))
		first.u.str = str;
	    break;
	}
	break;
#endif
    case FLOAT_:
	switch (second.op) {
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    dbl = first.u.dbl;
	    first.u.str = dbl2big(first.u.dbl);
	    leng1 = strlen(first.u.str);
	    leng2 = strlen(second.u.str);
	    leng = max(leng1, leng2) + env->scale;
	    leng = min(leng, 10);
	    str = GC_malloc_atomic(leng + 1);
	    if (num_div(first.u.str, second.u.str, str, leng)) {
		first.u.str = str;
	    	first.op = BIGNUM_;
	    } else
		first.u.dbl = dbl;
	    break;
#endif
	case FLOAT_:
	    first.u.dbl /= second.u.dbl;
	    break;

	default:
	    first.u.dbl /= second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    num = first.u.num;
	    first.u.str = num2big(first.u.num);
	    leng1 = strlen(first.u.str);
	    leng2 = strlen(second.u.str);
	    leng = max(leng1, leng2) + env->scale;
	    leng = min(leng, 10);
	    str = GC_malloc_atomic(leng + 1);
	    if (num_div(first.u.str, second.u.str, str, leng)) {
		first.u.str = str;
		first.op = BIGNUM_;
	    } else
		first.u.num = num;
	    break;
#endif
	case FLOAT_:
	    second.u.dbl = first.u.num / second.u.dbl;
	    env->stck = pvec_add(env->stck, second);
	    return;

	default:
	    first.u.num /= second.u.num;
	    break;
	}
	break;
    }
    env->stck = pvec_add(env->stck, first);
}
#endif
