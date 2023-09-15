/*
    module  : mul.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef MUL_C
#define MUL_C

/**
OK 1400  *\0mul  :  DDA	I J  ->  K
Integer K is the product of integers I and J.  Also supports float.
*/
void mul_(pEnv env)
{
    int sign1, sign2;
    Node first, second;
    int64_t num, num1, num2;

    PARM(2, MUL);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    switch (first.op) {
#ifdef USE_BIGNUM_ARITHMETIC
    case BIGNUM_:
	switch (second.op) {
	case BIGNUM_:
	    first.u.str = num_str_mul(first.u.str, second.u.str);
	    break;

	case FLOAT_:
	    second.u.str = dbl2big(second.u.dbl);
	    first.u.str = num_str_mul(first.u.str, second.u.str);
	    break;

	default:
	    second.u.str = num2big(second.u.num);
	    first.u.str = num_str_mul(first.u.str, second.u.str);
	    break;
	}
	break;
#endif
    case FLOAT_:
	switch (second.op) {
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    first.u.str = dbl2big(first.u.dbl);
	    first.u.str = num_str_mul(first.u.str, second.u.str);
	    first.op = BIGNUM_;
	    break;
#endif
	case FLOAT_:
	    first.u.dbl *= second.u.dbl;
	    break;

	default:
	    first.u.dbl *= second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    first.u.str = num2big(first.u.num);
	    first.u.str = num_str_mul(first.u.str, second.u.str);
	    first.op = BIGNUM_;
	    break;
#endif
	case FLOAT_:
	    second.u.dbl *= first.u.num;
	    first.u.dbl = second.u.dbl;
	    first.op = FLOAT_;
	    break;

	default:
	    num1 = first.u.num;
	    num2 = second.u.num;
	    if ((sign1 = num1 < 0) != 0) /* make positive */
		num1 = -num1;
	    if ((sign2 = num2 < 0) != 0) /* make positive */
		num2 = -num2;
#ifdef USE_BIGNUM_ARITHMETIC
	    if (num1 > MAXINT / num2 || num2 > MAXINT / num1) { /* overflow */
		first.u.str = num2big(num1);
		second.u.str = num2big(num2);
		first.u.str = num_str_mul(first.u.str, second.u.str);
		first.op = BIGNUM_;
		if (sign1 ^ sign2) /* insert the sign back, if they differ */
		    *first.u.str = '-';
	    } else {
#endif
		num = num1 * num2;
		if (sign1 ^ sign2) /* insert the sign back */
		    num = -num;
		first.u.num = num;
#ifdef USE_BIGNUM_ARITHMETIC
	    }
#endif
	    break;
	}
	break;
    }
    lst_push(env->stck, first);
}
#endif
