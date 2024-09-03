/*
    module  : parm.c
    date    : 1.22
    version : 09/01/24
*/
#include "globals.h"

/*
    check the number of parameters and if not sufficient call execerror.
*/
void checknum(int num, int leng, char *file)
{
    char *ptr = 0;

    if (num > leng)
	switch (num) {
	case 1: ptr = "one parameter";
		break;
	case 2: ptr = "two parameters";
		break;
	case 3: ptr = "three parameters";
		break;
	case 4: ptr = "four parameters";
		break;
	case 5: ptr = "five parameters";
		break;
	}
    if (ptr)
	execerror(ptr, file);
}

/*
    check parameters, all of them
*/
void parm(pEnv env, int num, Params type, char *file)
{
    int i, j;
    unsigned leng;
    Node first, second, third, fourth;

    leng = pvec_cnt(env->stck);
    checknum(num, leng, file);
/*
    check number and type of parameters:
*/
    switch (type) {
    case ANYTYPE:
	break;
/*
    one quote is needed:
*/
    case DIP:
	first = pvec_lst(env->stck);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	break;
/*
    two quotes are needed:
*/
    case WHILE:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != LIST_)
	    execerror("quotation as second parameter", file);
	break;
/*
    three quotes are needed:
*/
    case IFTE:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	third = pvec_nth(env->stck, leng - 3);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != LIST_)
	    execerror("quotation as second parameter", file);
	if (third.op != LIST_)
	    execerror("quotation as third parameter", file);
	break;
/*
    four quotes are needed:
*/
    case LINREC:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	third = pvec_nth(env->stck, leng - 3);
	fourth = pvec_nth(env->stck, leng - 4);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != LIST_)
	    execerror("quotation as second parameter", file);
	if (third.op != LIST_)
	    execerror("quotation as third parameter", file);
	if (fourth.op != LIST_)
	    execerror("quotation as fourth parameter", file);
	break;
/*
    list is needed:
*/
    case HELP:
	first = pvec_lst(env->stck);
	if (first.op != LIST_)
	    execerror("list", file);
	break;
/*
    list is needed as second parameter:
*/
    case INFRA:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != LIST_)
	    execerror("list as second parameter", file);
	break;
/*
    float or integer is needed:
*/
    case UFLOAT:
	first = pvec_lst(env->stck);
	if (first.op != FLOAT_ && first.op != INTEGER_)
	    execerror("float or integer", file);
	break;
/*
    two floats or integers are needed:
*/
    case MUL:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != BIGNUM_ && first.op != FLOAT_ && first.op != INTEGER_)
	    execerror("float or (big)integer", file);
	if (second.op != BIGNUM_ && second.op != FLOAT_ &&
	    second.op != INTEGER_)
	    execerror("two floats or (big)integers", file);
	break;
/*
    two floats or integers are needed:
*/
    case BFLOAT:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != FLOAT_ && first.op != INTEGER_)
	    execerror("float or integer", file);
	if (second.op != FLOAT_ && second.op != INTEGER_)
	    execerror("two floats or integers", file);
	break;
/*
    file is needed:
*/
    case FGET:
	first = pvec_lst(env->stck);
	if (first.op != FILE_ || !first.u.fil)
	    execerror("file", file);
	break;
/*
    file is needed as second parameter:
*/
    case FPUT:
	second = pvec_nth(env->stck, leng - 2);
	if (second.op != FILE_ || !second.u.fil)
	    execerror("file", file);
	break;
/*
    string is needed:
*/
    case STRFTIME:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != STRING_)
	    execerror("string", file);
	if (second.op != LIST_)
	    execerror("list as second parameter", file);
	break;

    case FPUTCHARS:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != STRING_ && first.op != BIGNUM_)
	    execerror("string", file);
	if (second.op != FILE_ || !second.u.fil)
	    execerror("file", file);
	break;

    case STRTOD:
	first = pvec_lst(env->stck);
	if (first.op != STRING_ && first.op != BIGNUM_)
	    execerror("string", file);
	break;
/*
    string is needed as second parameter:
*/
    case FOPEN:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != STRING_)
	    execerror("string", file);
	if (second.op != STRING_)
	    execerror("string as second parameter", file);
	break;
/*
    integer is needed:
*/
    case UNMKTIME:
	first = pvec_lst(env->stck);
	if (first.op != INTEGER_)
	    execerror("integer", file);
	break;

    case FREAD:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != INTEGER_ && first.op != CHAR_ && first.op != BOOLEAN_)
	    execerror("numeric", file);
	if (second.op != FILE_ || !second.u.fil)
	    execerror("file", file);
	break;

    case LDEXP:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != INTEGER_)
	    execerror("integer", file);
	if (second.op != FLOAT_ && second.op != INTEGER_)
	    execerror("float or integer as second parameter", file);
	break;

    case STRTOL:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != INTEGER_)
	    execerror("integer", file);
	if (second.op != STRING_ && second.op != BIGNUM_)
	    execerror("string as second parameter", file);
	break;
/*
    two integers are needed:
*/
    case FSEEK:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	third = pvec_nth(env->stck, leng - 3);
	if (first.op != INTEGER_ || second.op != INTEGER_)
	    execerror("two integers", file);
	if (third.op != FILE_ || !third.u.fil)
	    execerror("file", file);
	break;
/*
    integer is needed as second parameter:
*/
    case TIMES:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != INTEGER_)
	    execerror("integer as second parameter", file);
	if (second.u.num < 0)
	    execerror("non-negative integer", file);
	break;
/*
    numeric type is needed:
*/
    case MAXMIN:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if ((first.op == FLOAT_ || first.op == INTEGER_) &&
	    (second.op == FLOAT_ || second.op == INTEGER_))
	    ;
	else if (first.op != INTEGER_ && first.op != CHAR_ &&
		 first.op != BOOLEAN_ && second.op != INTEGER_ &&
		 second.op != CHAR_ && second.op != BOOLEAN_)
	    execerror("numeric", file);
	else if (first.op != second.op)
	    execerror("two parameters of the same type", file);
	break;
/*
    numeric type is needed:
*/
    case PREDSUCC:
	first = pvec_lst(env->stck);
	if (first.op != INTEGER_ && first.op != CHAR_ && first.op != BOOLEAN_ &&
	    first.op != BIGNUM_)
	    execerror("numeric", file);
	break;
/*
    numeric type is needed as second parameter:
*/
    case PLUSMINUS:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if ((first.op == BIGNUM_ || first.op == FLOAT_ || first.op == INTEGER_)
	    && (second.op == BIGNUM_ || second.op == FLOAT_ ||
	    second.op == INTEGER_))
	    ;
	else if (first.op != INTEGER_)
	    execerror("integer", file);
	else if (second.op != INTEGER_ && second.op != CHAR_)
	    execerror("numeric as second parameter", file);
	break;
/*
    aggregate parameter is needed:
*/
    case SIZE_:
	first = pvec_lst(env->stck);
	if (first.op != LIST_ && first.op != STRING_ && first.op != SET_ &&
	    first.op != BIGNUM_)
	    execerror("aggregate parameter", file);
	break;
/*
    aggregate parameter is needed as second parameter:
*/
    case STEP:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != LIST_ && second.op != STRING_ && second.op != SET_ &&
	    second.op != BIGNUM_)
	    execerror("aggregate parameter", file);
	break;

    case TAKE:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != INTEGER_ || first.u.num < 0)
	    execerror("non-negative integer", file);
	if (second.op != LIST_ && second.op != STRING_ && second.op != SET_ &&
	    second.op != BIGNUM_)
	    execerror("aggregate parameter", file);
	break;
/*
    two parameters of the same type are needed:
*/
    case CONCAT:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != LIST_ && first.op != STRING_ && first.op != SET_ &&
	    second.op != BIGNUM_)
	    execerror("aggregate parameter", file);
	if (first.op != second.op)
	    execerror("two parameters of the same type", file);
	break;
/*
    specific number of types:
*/
    case ANDORXOR:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != second.op)
	    execerror("two parameters of the same type", file);
	if (first.op != SET_ && first.op != INTEGER_ && first.op != CHAR_ &&
	    first.op != BOOLEAN_)
	    execerror("different type", file);
	break;

    case NOT:
	first = pvec_lst(env->stck);
	if (first.op != SET_ && first.op != INTEGER_ && first.op != CHAR_ &&
	    first.op != BOOLEAN_)
	    execerror("different type", file);
	break;
/*
    specific number of types:
*/
    case PRIMREC:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	third = pvec_nth(env->stck, leng - 3);
	if (first.op != LIST_ || second.op != LIST_)
	    execerror("two quotations", file);
	if (third.op != LIST_ && third.op != STRING_ && third.op != SET_ &&
	    third.op != INTEGER_)
	    execerror("different type", file);
	break;
/*
    specific number of types:
*/
    case SMALL:
	first = pvec_lst(env->stck);
	if (first.op != LIST_ && first.op != STRING_ && first.op != SET_ &&
	    first.op != INTEGER_ && first.op != BOOLEAN_ && first.op != BIGNUM_)
	    execerror("different type", file);
	break;
/*
    user defined symbol:
*/
    case BODY:
	first = pvec_lst(env->stck);
	if (first.op != USR_)
	    execerror("user defined symbol", file);
	break;
/*
    valid symbol name:
*/
    case INTERN:
	first = pvec_lst(env->stck);
	if (first.op != STRING_)
	    execerror("string", file);
	/*
	    a negative number is not a valid name
	*/
	if (first.u.str[0] == '-' && isdigit((int)first.u.str[1]))
	    execerror("valid name", file);
	/*
	    a name that starts with any of these characters is not valid
	*/
	if (strchr("\"#'().0123456789;[]{}", first.u.str[0]))
	    execerror("valid name", file);
	/*
	    a name consists of alphanumeric characters, or one of the dashes
	*/
	for (i = strlen(first.u.str) - 1; i > 0; i--)
	     if (!isalnum((int)first.u.str[i]) &&
		 !strchr("-=_", first.u.str[i]))
		 execerror("valid name", file);
	break;
/*
    character:
*/
    case FORMAT:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	third = pvec_nth(env->stck, leng - 3);
	fourth = pvec_nth(env->stck, leng - 4);
	if (first.op != INTEGER_ || second.op != INTEGER_)
	    execerror("two integers", file);
	if (third.op != CHAR_)
	    execerror("character", file);
	if (!strchr("dioxX", third.u.num))
	    execerror("one of: d i o x X", file);
	if (fourth.op != INTEGER_ && fourth.op != CHAR_ &&
	    fourth.op != BOOLEAN_)
	    execerror("numeric as fourth parameter", file);
	break;

    case FORMATF:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	third = pvec_nth(env->stck, leng - 3);
	fourth = pvec_nth(env->stck, leng - 4);
	if (first.op != INTEGER_ || second.op != INTEGER_)
	    execerror("two integers", file);
	if (third.op != CHAR_)
	    execerror("character", file);
	if (!strchr("eEfgG", third.u.num))
	    execerror("one of: e E f g G", file);
	if (fourth.op != FLOAT_)
	    execerror("float as fourth parameter", file);
	break;
/*
    set member:
*/
    case CONS:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	switch (first.op) {
	case LIST_:
	    break;
	case STRING_:
	case BIGNUM_:
	    if (second.op != CHAR_)
		execerror("character", file);
	    break;
	case SET_:
	    if ((second.op != INTEGER_ && second.op != CHAR_) ||
		 second.u.num < 0 || second.u.num >= SETSIZE)
		execerror("small numeric", file);
	    break;
	default:
	    execerror("aggregate parameter", file);
	}
	break;
/*
    set member:
*/
    case IN_:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	switch (first.op) {
	case LIST_:
	    break;
	case STRING_:
	case BIGNUM_:
#if 0
	    if (second.op != CHAR_)
		execerror("character", file);
#endif
	    break;
	case SET_:
	    if ((second.op != INTEGER_ && second.op != CHAR_) ||
		 second.u.num < 0 || second.u.num >= SETSIZE)
		execerror("small numeric", file);
	    break;
	default:
	    execerror("aggregate parameter", file);
	}
	break;
/*
    set member:
*/
    case HAS:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	switch (second.op) {
	case LIST_:
	    break;
	case STRING_:
	case BIGNUM_:
#if 0
	    if (first.op != CHAR_)
		execerror("character", file);
#endif
	    break;
	case SET_:
	    if ((first.op != INTEGER_ && first.op != CHAR_) ||
		 first.u.num < 0 || first.u.num >= SETSIZE)
		execerror("small numeric", file);
	    break;
	default:
	    execerror("aggregate parameter", file);
	}
	break;
/*
    check empty list:
*/
    case CASE:
	first = pvec_lst(env->stck);
	if (first.op != LIST_)
	    execerror("list", file);
	if (!pvec_cnt(first.u.lis))
	    execerror("non-empty list", file);
	for (i = pvec_cnt(first.u.lis) - 1; i >= 0; i--) {
	    second = pvec_nth(first.u.lis, i);
	    if (second.op != LIST_)
		execerror("internal list", file);
	}
	break;
/*
    check empty aggregate:
*/
    case FIRST:
	first = pvec_lst(env->stck);
	switch (first.op) {
	case LIST_:
	    if (!pvec_cnt(first.u.lis))
		execerror("non-empty list", file);
	    break;
	case STRING_:
	case BIGNUM_:
	    if (!*first.u.str)
		execerror("non-empty string", file);
	    break;
	case SET_:
	    if (!first.u.set)
		execerror("non-empty set", file);
	    break;
	default:
	    execerror("aggregate parameter", file);
	}
	break;
/*
    check empty aggregate:
*/
    case OF:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (second.u.num < 0)
	    execerror("non-negative integer", file);
	switch (first.op) {
	case LIST_  : if (!pvec_cnt(first.u.lis))
			  execerror("non-empty list", file);
		      if (second.u.num >= pvec_cnt(first.u.lis))
			  execerror("smaller index", file);
		      break;
	case STRING_:
	case BIGNUM_: if (!*first.u.str)
			  execerror("non-empty string", file);
		      if (second.u.num >= (int)strlen(first.u.str))
			  execerror("smaller index", file);
		      break;
	case SET_   : if (!first.u.set)
			  execerror("non-empty set", file);
		      for (i = 0, j = second.u.num; i < SETSIZE; i++)
			  if (first.u.set & ((int64_t)1 << i)) {
			      if (!j)
				  return;
			      j--;
			  }
		      execerror("smaller index", file);
		      break;
	default     : execerror("aggregate parameter", file); 
	}
	break;

    case AT:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.u.num < 0)
	    execerror("non-negative integer", file);
	switch (second.op) {
	case LIST_  : if (!pvec_cnt(second.u.lis))
			  execerror("non-empty list", file);
		      if (first.u.num >= pvec_cnt(second.u.lis))
			  execerror("smaller index", file);
		      break;
	case STRING_:
	case BIGNUM_: if (!*second.u.str)
			  execerror("non-empty string", file);
		      if (first.u.num >= (int)strlen(second.u.str))
			  execerror("smaller index", file);
		      break;
	case SET_   : if (!second.u.set)
			  execerror("non-empty set", file);
		      for (i = 0, j = first.u.num; i < SETSIZE; i++)
			  if (second.u.set & ((int64_t)1 << i)) {
			      if (!j)
				  return;
			      j--;
			  }
		      execerror("smaller index", file);
		      break;
	default     : execerror("aggregate parameter", file);
	}
	break;
/*
    check second operand:
*/
    case DIV:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != INTEGER_ || second.op != INTEGER_)
	    execerror("two integers", file);
	if (!first.u.num)
	    execerror("non-zero operand", file);
	break;

    case REM:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != FLOAT_ && first.op != INTEGER_)
	    execerror("float or integer", file);
	if (second.op != FLOAT_ && second.op != INTEGER_)
	    execerror("two floats or integers", file);
	if ((first.op == FLOAT_ && !first.u.dbl) || !first.u.num)
	    execerror("non-zero operand", file);
	break;

    case DIVIDE:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != BIGNUM_ && first.op != FLOAT_ && first.op != INTEGER_)
	    execerror("float or integer", file);
	if (second.op != BIGNUM_ && second.op != FLOAT_ &&
	    second.op != INTEGER_)
	    execerror("two floats or integers", file);
	if ((first.op == BIGNUM_ && first.u.str[1] == '0') ||
	    (first.op == FLOAT_ && !first.u.dbl) || !first.u.num)
	    execerror("non-zero divisor", file);
	break;
/*
    check numeric list:
*/
    case FWRITE:
	first = pvec_lst(env->stck);
	second = pvec_nth(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("list", file);
	if (second.op != FILE_ || !second.u.fil)
	    execerror("file", file);
	for (i = pvec_cnt(first.u.lis) - 1; i >= 0; i--) {
	    second = pvec_nth(first.u.lis, i);
	    if (second.op != INTEGER_)
		execerror("numeric list", file);
	}
	break;
/*
 * check list at top with user defined symbol.
 */
    case ASSIGN:
	first = pvec_lst(env->stck);
	if (first.op != LIST_)
	    execerror("list", file);
	if (!pvec_cnt(first.u.lis))
	    execerror("non-empty list", file);
	first = pvec_lst(first.u.lis);
	if (first.op != USR_)
	    execerror("user defined symbol", file);
	break;
#ifdef USE_MULTI_THREADS_JOY
/*
    channel as top parameter:
*/
    case RECEIVE:
	first = pvec_lst(env->stck);
	if (first.op != INTEGER_)
	    execerror("channel", file);
	break;
/*
    channel as second parameter:
*/
    case SEND:
	second = pvec_nth(env->stck, leng - 2);
	if (second.op != INTEGER_)
	    execerror("channel", file);
	break;
#endif
    }
}
