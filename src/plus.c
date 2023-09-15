/*
    module  : plus.c
    version : 1.8
    date    : 09/15/23
*/
#ifndef PLUS_C
#define PLUS_C

/**
OK 1380  +\0plus  :  DDA	M I  ->  N
Numeric N is the result of adding integer I to numeric M.
Also supports float.
*/
void plus_(pEnv env)
{
    Node first, second;
#ifdef USE_BIGNUM_ARITHMETIC
    int sign1, sign2;
    int64_t num, num1, num2;
#endif

    PARM(2, PLUSMINUS);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    switch (first.op) {
#ifdef USE_BIGNUM_ARITHMETIC
    case BIGNUM_:
	switch (second.op) {
	case BIGNUM_:
	    first.u.str = num_str_add(first.u.str, second.u.str);
	    break;

	case FLOAT_:
	    second.u.str = dbl2big(second.u.dbl);
	    first.u.str = num_str_add(first.u.str, second.u.str);
	    break;

	default:
	    second.u.str = num2big(second.u.num);
	    first.u.str = num_str_add(first.u.str, second.u.str);
	    break;
	}
	break;
#endif
    case FLOAT_:
	switch (second.op) {
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    first.u.str = dbl2big(first.u.dbl);
	    first.u.str = num_str_add(first.u.str, second.u.str);
	    first.op = BIGNUM_;
	    break;
#endif
	case FLOAT_:
	    first.u.dbl += second.u.dbl;
	    break;

	default:
	    first.u.dbl += second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    first.u.str = num2big(first.u.num);
	    first.u.str = num_str_add(first.u.str, second.u.str);
	    first.op = BIGNUM_;
	    break;
#endif
	case FLOAT_:
	    second.u.dbl += first.u.num;
	    first.u.dbl = second.u.dbl;
	    first.op = FLOAT_;
	    break;

	default:
#ifdef USE_BIGNUM_ARITHMETIC
	    num1 = first.u.num;
	    num2 = second.u.num;
	    sign1 = num1 < 0;
	    sign2 = num2 < 0;
	    if (sign1 == sign2) { /* possible overflow when doing addition */
		if (sign1) { /* make positive */
		    num1 = -num1;
		    num2 = -num2;
		}
		num = num1 + num2; /* unsigned addition, possible wrap around */
		if (num < num1 || num < num2) { /* test overflow */
		    first.u.str = num2big(num1);
		    second.u.str = num2big(num2);
		    first.u.str = num_str_add(first.u.str, second.u.str);
		    first.op = BIGNUM_;
		    if (sign1) /* insert the sign back */
			*first.u.str = '-';
		} else {
		    if (sign1) /* insert the sign back */
			num = -num;
		    first.u.num = num;
		}
	    } else
#endif
		first.u.num += second.u.num; /* no overflow when subtracting */
	    break;
	}
	break;
    }
    lst_push(env->stck, first);
}
#endif
