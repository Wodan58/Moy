/*
    module  : compare.h
    version : 1.15
    date    : 11/06/23
*/
#ifndef COMPARE_H
#define COMPARE_H

/*
    BOOLEAN, CHAR, INTEGER, SET, FLOAT, BIGNUM are lumped together allowing
    numerical compare; USR, ANON_FUNCT, STRING, BIGNUM are lumped together
    allowing string compare; FILE can only be compared with FILE; LIST cannot
    be compared with anything.
*/
PUBLIC int Compare(pEnv env, Node first, Node second)
{
    FILE *fp1, *fp2;
    char *name1, *name2;
    double dbl1 = 0, dbl2 = 0;
    int64_t num1 = 0, num2 = 0;
#ifdef USE_BIGNUM_ARITHMETIC
    char str[2];

    str[1] = 0;
#endif
    switch (first.op) {
    case USR_:
    case USR_PRIME_:
	name1 = vec_at(env->symtab, first.u.ent).name;
	switch (second.op) {
	case USR_:
	case USR_PRIME_:
	    name2 = vec_at(env->symtab, second.u.ent).name;
	    goto cmpstr;
	case ANON_FUNCT_:
	case ANON_PRIME_:
	    name2 = cmpname(second.u.proc);
	    goto cmpstr;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	default:
	    return 1; /* unequal */
	case STRING_:
	case BIGNUM_:
	case USR_STRING_:
	    name2 = second.u.str;
	    goto cmpstr;
	}
	break;
    case ANON_FUNCT_:
    case ANON_PRIME_:
	name1 = cmpname(first.u.proc);
	switch (second.op) {
	case USR_:
	case USR_PRIME_:
	    name2 = vec_at(env->symtab, second.u.ent).name;
	    goto cmpstr;
	case ANON_FUNCT_:
	case ANON_PRIME_:
	    name2 = cmpname(second.u.proc);
	    goto cmpstr;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	default:
	    return 1; /* unequal */
	case STRING_:
	case BIGNUM_:
	case USR_STRING_:
	    name2 = second.u.str;
	    goto cmpstr;
	}
	break;
    case BOOLEAN_:
	num1 = first.u.num;
	switch (second.op) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    num2 = second.u.num;
	    goto cmpnum;
	case FLOAT_:
	    dbl1 = num1;
	    dbl2 = second.u.dbl;
	    goto cmpdbl;
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    name1 = num1 ? "1" : "0";
	    name2 = second.u.str;
	    goto cmpbig;
	    break;
#endif
	default:
	    return 1; /* unequal */
	}
	break;
    case CHAR_:
	num1 = first.u.num;
	switch (second.op) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    num2 = second.u.num;
	    goto cmpnum;
	case FLOAT_:
	    dbl1 = num1;
	    dbl2 = second.u.dbl;
	    goto cmpdbl;
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    str[0] = (char)first.u.num;
	    name1 = str;
	    name2 = second.u.str;
	    goto cmpbig;
	    break;
#endif
	default:
	    return 1; /* unequal */
	}
	break;
    case INTEGER_:
	num1 = first.u.num;
	switch (second.op) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    num2 = second.u.num;
	    goto cmpnum;
	case FLOAT_:
	    dbl1 = num1;
	    dbl2 = second.u.dbl;
	    goto cmpdbl;
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    name1 = num2big(num1);
	    name2 = second.u.str;
	    goto cmpbig;
	    break;
#endif
	default:
	    return 1; /* unequal */
	}
	break;
    case SET_:
	num1 = first.u.num;
	switch (second.op) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case FLOAT_:
	    num2 = second.u.num;
	    goto cmpnum;
	    break;
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    name1 = num2big(num1);
	    name2 = second.u.str;
	    goto cmpbig;
	    break;
#endif
	case USR_:
	case USR_PRIME_:
	case ANON_FUNCT_:
	case ANON_PRIME_:
	case STRING_:
	case USR_STRING_:
	case LIST_:
	case USR_LIST_:
	default:
	    return 1; /* unequal */
	}
	break;
    case STRING_:
    case USR_STRING_:
	name1 = first.u.str;
	switch (second.op) {
	case USR_:
	case USR_PRIME_:
	    name2 = vec_at(env->symtab, second.u.ent).name;
	    goto cmpstr;
	case ANON_FUNCT_:
	case ANON_PRIME_:
	    name2 = cmpname(second.u.proc);
	    goto cmpstr;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	default:
	    return 1; /* unequal */
	case STRING_:
	case BIGNUM_:
	case USR_STRING_:
	    name2 = second.u.str;
	    goto cmpstr;
	}
	break;
    case LIST_:
    case USR_LIST_:
	return 1; /* unequal */
	break;
    case FLOAT_:
	dbl1 = first.u.dbl;
	switch (second.op) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	    dbl2 = second.u.num;
	    goto cmpdbl;
	case SET_:
	    num1 = first.u.num;
	    num2 = second.u.num;
	    goto cmpnum;
	case FLOAT_:
	    dbl2 = second.u.dbl;
	    goto cmpdbl;
#ifdef USE_BIGNUM_ARITHMETIC
	case BIGNUM_:
	    name1 = dbl2big(dbl1);
	    name2 = second.u.str;
	    goto cmpbig;
	    break;
#endif
	default:
	    return 1; /* unequal */
	}
	break;
    case FILE_:
	fp1 = first.u.fil;
	switch (second.op) {
	case FILE_:
	    fp2 = second.u.fil;
	    return fp1 < fp2 ? -1 : fp1 > fp2;
	default:
	    return 1; /* unequal */
	}
	break;
#ifdef USE_BIGNUM_ARITHMETIC
    case BIGNUM_:
	name1 = first.u.str;
	switch (second.op) {
	case BOOLEAN_:
	    name2 = second.u.num ? "1" : "0";
	    goto cmpbig;
	case CHAR_:
	    str[0] = (char)first.u.num;
	    name2 = str;
	    goto cmpbig;
	case INTEGER_:
	case SET_:
	    name2 = num2big(second.u.num);
	    goto cmpbig;
	case STRING_:
	case BIGNUM_:
	case USR_STRING_:
	    name2 = second.u.str;
	    goto cmpbig;
	case FLOAT_:
	    name2 = dbl2big(second.u.dbl);
	    goto cmpbig;
	default:
	    return 1; /* unequal */
	}
	break;
#endif
    default:
	return 1; /* unequal */
    }
cmpnum:
    return num1 < num2 ? -1 : num1 > num2;
cmpdbl:
    return dbl1 < dbl2 ? -1 : dbl1 > dbl2;
cmpstr:
    num1 = strcmp(name1, name2);
    return num1 < 0 ? -1 : num1 > 0;
#ifdef USE_BIGNUM_ARITHMETIC
cmpbig:
    num1 = num_cmp(name1, name2);
    return num1 < 0 ? -1 : num1 > 0;
#endif
}
#endif
