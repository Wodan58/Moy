/*
    module  : minus.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef MINUS_C
#define MINUS_C

/**
Q0  OK  1390  -\0minus  :  DDA  M I  ->  N
Numeric N is the result of subtracting integer I from numeric M.
Also supports float.
*/
void minus_(pEnv env)
{
    Node first, second;
#ifdef USE_BIGNUM_ARITHMETIC
    int sign1, sign2;
    int64_t num, num1, num2;
#endif

    PARM(2, PLUSMINUS);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    switch (first.op) {
#ifdef USE_BIGNUM_ARITHMETIC
    case BIGNUM_:
	switch (second.op) {
	case BIGNUM_:
	    first.u.str = num_str_sub(first.u.str, second.u.str);
	    break;

	case FLOAT_:
	    second.u.str = dbl2big(second.u.dbl);
	    first.u.str = num_str_sub(first.u.str, second.u.str);
	    break;

	default:
	    second.u.str = num2big(second.u.num);
	    first.u.str = num_str_sub(first.u.str, second.u.str);
	    break;
	}
	break;
#endif
    case FLOAT_:
	switch (second.op) {
	case FLOAT_:
	    first.u.dbl -= second.u.dbl;
	    break;

	default:
	    first.u.dbl -= second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    first.u.str = dbl2big(first.u.dbl);
	    first.u.str = num_str_sub(first.u.str, second.u.str);
	    first.op = BIGNUM_;
	    break;
#endif
	case FLOAT_:
	    first.u.dbl = first.u.num - second.u.dbl;
	    first.op = FLOAT_;
	    break;

	default:
#ifdef USE_BIGNUM_ARITHMETIC
	    num1 = first.u.num;
	    num2 = second.u.num;
	    sign1 = num1 < 0;
	    sign2 = num2 < 0;
	    if (!sign1 && sign2) { /* overflow possible */
		num2 = -num2;
		num = num1 + num2; /* unsigned addition, possible wrap around */
		if (num < num1 || num < num2) { /* test overflow */
		    first.u.str = num2big(num1);
		    second.u.str = num2big(num2);
		    first.u.str = num_str_add(first.u.str, second.u.str);
		    first.op = BIGNUM_;
		} else
		    first.u.num += num2;
	    } else
#endif
		first.u.num -= second.u.num;
	    break;
	}
	break;
    }
    vec_push(env->stck, first);
}
#endif
