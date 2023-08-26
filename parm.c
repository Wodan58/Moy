/*
    module  : %M%
    date    : %I%
    version : %G%
*/
#include "globals.h"

/*
    check the number of parameters and if not sufficient call execerror.
*/
PRIVATE void checknum(int num, int leng, char *file)
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
PUBLIC void parm(pEnv env, int num, Params type, char *file)
{
    int i, j;
    unsigned leng;
    Node first, second, third, fourth;

    leng = lst_size(env->stck);
/*
    check number and type of parameters:
*/
    switch (type) {
    case ANYTYPE:
	checknum(num, leng, file);
	break;
/*
    one quote is needed:
*/
    case DIP:
	checknum(num, leng, file);
	first = lst_back(env->stck);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	break;
/*
    two quotes are needed:
*/
    case WHILE:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != LIST_)
	    execerror("quotation as second parameter", file);
	break;
/*
    three quotes are needed:
*/
    case IFTE:
	if (leng < 3)
	    execerror("three parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	third = lst_at(env->stck, leng - 3);
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
	if (leng < 4)
	    execerror("four parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	third = lst_at(env->stck, leng - 3);
	fourth = lst_at(env->stck, leng - 4);
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
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != LIST_)
	    execerror("list", file);
	break;
/*
    list is needed as second parameter:
*/
    case INFRA:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != LIST_)
	    execerror("list as second parameter", file);
	break;
/*
    float or integer is needed:
*/
    case UFLOAT:
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != FLOAT_ && first.op != INTEGER_)
	    execerror("float or integer", file);
	break;
/*
    two floats or integers are needed:
*/
    case MUL:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
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
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != FLOAT_ && first.op != INTEGER_)
	    execerror("float or integer", file);
	if (second.op != FLOAT_ && second.op != INTEGER_)
	    execerror("two floats or integers", file);
	break;
/*
    file is needed:
*/
    case FGET:
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != FILE_ || !first.u.fil)
	    execerror("file", file);
	break;
/*
    file is needed as second parameter:
*/
    case FPUT:
	if (leng < 2)
	    execerror("two parameters", file);
	second = lst_at(env->stck, leng - 2);
	if (second.op != FILE_ || !second.u.fil)
	    execerror("file", file);
	break;
/*
    string is needed:
*/
    case STRFTIME:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != STRING_)
	    execerror("string", file);
	if (second.op != LIST_)
	    execerror("list as second parameter", file);
	break;
    case FPUTCHARS:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != STRING_ && first.op != BIGNUM_)
	    execerror("string", file);
	if (second.op != FILE_ || !second.u.fil)
	    execerror("file", file);
	break;
    case STRTOD:
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != STRING_)
	    execerror("string", file);
	break;
/*
    string is needed as second parameter:
*/
    case FOPEN:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != STRING_)
	    execerror("string", file);
	if (second.op != STRING_)
	    execerror("string as second parameter", file);
	break;
/*
    integer is needed:
*/
    case UNMKTIME:
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != INTEGER_)
	    execerror("integer", file);
	break;
    case FREAD:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != INTEGER_)
	    execerror("integer", file);
	if (second.op != FILE_ || !second.u.fil)
	    execerror("file", file);
	break;
    case LDEXP:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != INTEGER_)
	    execerror("integer", file);
	if (second.op != FLOAT_ && second.op != INTEGER_)
	    execerror("float or integer as second parameter", file);
	break;
    case STRTOL:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != INTEGER_)
	    execerror("integer", file);
	if (second.op != STRING_)
	    execerror("string as second parameter", file);
	break;
/*
    two integers are needed:
*/
    case FSEEK:
	if (leng < 3)
	    execerror("three parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	third = lst_at(env->stck, leng - 3);
	if (first.op != INTEGER_ || second.op != INTEGER_)
	    execerror("two integers", file);
	if (third.op != FILE_ || !third.u.fil)
	    execerror("file", file);
	break;
/*
    integer is needed as second parameter:
*/
    case TIMES:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != INTEGER_)
	    execerror("integer as second parameter", file);
	break;
/*
    numeric type is needed:
*/
    case MAXMIN:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
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
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != INTEGER_ && first.op != CHAR_ && first.op != BOOLEAN_)
	    execerror("numeric", file);
	break;
/*
    numeric type is needed as second parameter:
*/
    case PLUSMINUS:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
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
    case SIZE:
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != LIST_ && first.op != STRING_ && first.op != SET_ &&
	    first.op != BIGNUM_)
	    execerror("aggregate parameter", file);
	break;
/*
    aggregate parameter is needed as second parameter:
*/
    case STEP:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("quotation as top parameter", file);
	if (second.op != LIST_ && second.op != STRING_ && second.op != SET_ &&
	    second.op != BIGNUM_)
	    execerror("aggregate parameter", file);
	break;
    case TAKE:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
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
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
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
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != second.op)
	    execerror("two parameters of the same type", file);
	if (first.op != SET_ && first.op != INTEGER_ && first.op != CHAR_ &&
	    first.op != BOOLEAN_)
	    execerror("different type", file);
	break;
    case NOT:
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != SET_ && first.op != INTEGER_ && first.op != CHAR_ &&
	    first.op != BOOLEAN_)
	    execerror("different type", file);
	break;
/*
    specific number of types:
*/
    case PRIMREC:
	if (leng < 3)
	    execerror("three parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	third = lst_at(env->stck, leng - 3);
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
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != LIST_ && first.op != STRING_ && first.op != SET_ &&
	    first.op != INTEGER_ && first.op != BOOLEAN_ && first.op != BIGNUM_)
	    execerror("different type", file);
	break;
/*
    user defined symbol:
*/
    case BODY:
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	if (first.op != USR_)
	    execerror("user defined symbol", file);
	break;
/*
    valid symbol name:
*/
    case INTERN:
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
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
	if (leng < 4)
	    execerror("four parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	third = lst_at(env->stck, leng - 3);
	fourth = lst_at(env->stck, leng - 4);
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
	if (leng < 4)
	    execerror("four parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	third = lst_at(env->stck, leng - 3);
	fourth = lst_at(env->stck, leng - 4);
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
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
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
    case HAS:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	switch (second.op) {
	case LIST_:
	    break;
	case STRING_:
	case BIGNUM_:
	    if (first.op != CHAR_)
		execerror("character", file);
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
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	if (first.op != LIST_)
	    execerror("list", file);
	if (!lst_size(first.u.lis))
	    execerror("non-empty list", file);
	for (i = lst_size(first.u.lis) - 1; i >= 0; i--) {
	    second = lst_at(first.u.lis, i);
	    if (second.op != LIST_)
		execerror("internal list", file);
	}
	break;
/*
    check empty aggregate:
*/
    case FIRST:
	if (leng < 1)
	    execerror("one parameter", file);
	first = lst_back(env->stck);
	switch (first.op) {
	case LIST_:
	    if (!lst_size(first.u.lis))
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
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (second.u.num < 0)
	    execerror("non-negative integer", file);
	switch (first.op) {
	case LIST_  : if (!lst_size(first.u.lis))
			  execerror("non-empty list", file);
		      if (second.u.num >= lst_size(first.u.lis))
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
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.u.num < 0)
	    execerror("non-negative integer", file);
	switch (second.op) {
	case LIST_  : if (!lst_size(second.u.lis))
			  execerror("non-empty list", file);
		      if (first.u.num >= lst_size(second.u.lis))
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
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != INTEGER_ || second.op != INTEGER_)
	    execerror("two integers", file);
	if (!first.u.num)
	    execerror("non-zero operand", file);
	break;
    case REM:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != FLOAT_ && first.op != INTEGER_)
	    execerror("float or integer", file);
	if (second.op != FLOAT_ && second.op != INTEGER_)
	    execerror("two floats or integers", file);
	if ((first.op == FLOAT_ && !first.u.dbl) || !first.u.num)
	    execerror("non-zero operand", file);
	break;
    case DIVIDE:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != FLOAT_ && first.op != INTEGER_)
	    execerror("float or integer", file);
	if (second.op != FLOAT_ && second.op != INTEGER_)
	    execerror("two floats or integers", file);
	if ((first.op == FLOAT_ && !first.u.dbl) || !first.u.num)
	    execerror("non-zero divisor", file);
	break;
/*
    check numeric list:
*/
    case FWRITE:
	if (leng < 2)
	    execerror("two parameters", file);
	first = lst_back(env->stck);
	second = lst_at(env->stck, leng - 2);
	if (first.op != LIST_)
	    execerror("list", file);
	if (second.op != FILE_ || !second.u.fil)
	    execerror("file", file);
	for (i = lst_size(first.u.lis) - 1; i >= 0; i--) {
	    second = lst_at(first.u.lis, i);
	    if (second.op != INTEGER_)
		execerror("numeric list", file);
	}
	break;
    }
}
