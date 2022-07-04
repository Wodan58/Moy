/*
    module  : runtime.h
    version : 1.22
    date    : 06/17/22
*/
#ifndef RUNTIME_H
#define RUNTIME_H

#include "globals.h"

typedef struct table_t {
    proc_t proc;
    char *name;
} table_t;

extern table_t table[];
extern clock_t startclock;

#ifdef COMPILING
#define TRACE
#define COMPILE								\
    if (compiling) {							\
	printstack(env);						\
	fprintf(outfp, "%s(env);", __func__);				\
	return;								\
    }
#define INSTANT(X)							\
    if (compiling) {							\
	printstack(env);						\
	X(env, prog);							\
	return;								\
    }
#else
#define TRACE		do { if (debugging) { writestack(env, env->stk);\
			printf(" : "); printf("%s\n", __func__); } } while (0)
#define COMPILE		TRACE
#define INSTANT(X)
#endif

#define PRIVATE

#define POP(x)		(x) = (x)->next;
#define DUPLICATE(x)	env->stk = newnode((x)->op, (x)->u, env->stk);
#define PUSH_NUM(x, y)							\
    do {								\
	YYSTYPE u;							\
	u.num = (y);							\
	env->stk = newnode((x), u, env->stk);				\
    } while (0)
#define PUSH_PTR(x, y)							\
    do {								\
	YYSTYPE u;							\
	u.ptr = (y);							\
	env->stk = newnode((x), u, env->stk);				\
    } while (0)
#define PUSH_DBL(x)							\
    do {								\
	YYSTYPE u;							\
	u.dbl = (x);							\
	env->stk = newnode(FLOAT_, u, env->stk);			\
    } while (0)

#define FLOATVAL							\
    (env->stk->op == FLOAT_ ? env->stk->u.dbl : (double)env->stk->u.num)
#define FLOATVAL2							\
    (env->stk->next->op == FLOAT_ ? env->stk->next->u.dbl		\
				  : (double)env->stk->next->u.num)

#define FLOATABLE (env->stk->op == INTEGER_ || env->stk->op == FLOAT_)
#define FLOATABLE2							\
    ((env->stk->op == FLOAT_ && env->stk->next->op == FLOAT_)		\
	|| (env->stk->op == FLOAT_ && env->stk->next->op == INTEGER_)	\
	|| (env->stk->op == INTEGER_ && env->stk->next->op == FLOAT_))
#define ONEPARAM(NAME)							\
    TRACE; if (!env->stk || library)					\
    { execerror(env, "one parameter", NAME); return; }
#define TWOPARAMS(NAME)							\
    TRACE; if (!env->stk || !env->stk->next || library)			\
    { execerror(env, "two parameters", NAME); return; }
#define THREEPARAMS(NAME)						\
    TRACE; if (!env->stk || !env->stk->next || !env->stk->next->next	\
	|| library)							\
    { execerror(env, "three parameters", NAME); return; }
#define FOURPARAMS(NAME)						\
    TRACE; if (!env->stk || !env->stk->next || !env->stk->next->next	\
	|| !env->stk->next->next->next || library)			\
    { execerror(env, "four parameters", NAME); return; }
#define FIVEPARAMS(NAME)						\
    if (!env->stk || !env->stk->next || !env->stk->next->next		\
	|| !env->stk->next->next->next || !env->stk->next->next->next->next) \
    { execerror(env, "five parameters", NAME); return; }
#define SIXPARAMS(NAME)							\
    if (!env->stk || !env->stk->next || !env->stk->next->next		\
	|| !env->stk->next->next->next || !env->stk->next->next->next->next \
	|| !env->stk->next->next->next->next->next)			\
    { execerror(env, "six parameters", NAME); return; }
#define SEVENPARAMS(NAME)						\
    if (!env->stk || !env->stk->next || !env->stk->next->next		\
	|| !env->stk->next->next->next || !env->stk->next->next->next->next \
	|| !env->stk->next->next->next->next->next			\
	|| !env->stk->next->next->next->next->next->next)		\
    { execerror(env, "seven parameters", NAME); return; }
#define EIGHTPARAMS(NAME)						\
    if (!env->stk || !env->stk->next || !env->stk->next->next		\
	|| !env->stk->next->next->next || !env->stk->next->next->next->next \
	|| !env->stk->next->next->next->next->next			\
	|| !env->stk->next->next->next->next->next->next		\
	|| !env->stk->next->next->next->next->next->next->next)		\
    { execerror(env, "eight parameters", NAME); return; }
#define NINEPARAMS(NAME)						\
    if (!env->stk || !env->stk->next || !env->stk->next->next		\
	|| !env->stk->next->next->next || !env->stk->next->next->next->next \
	|| !env->stk->next->next->next->next->next			\
	|| !env->stk->next->next->next->next->next->next		\
	|| !env->stk->next->next->next->next->next->next->next		\
	|| !env->stk->next->next->next->next->next->next->next->next)	\
    { execerror(env, "nine parameters", NAME); return; }
#define TENPARAMS(NAME)							\
    if (!env->stk || !env->stk->next || !env->stk->next->next		\
	|| !env->stk->next->next->next || !env->stk->next->next->next->next \
	|| !env->stk->next->next->next->next->next			\
	|| !env->stk->next->next->next->next->next->next		\
	|| !env->stk->next->next->next->next->next->next->next		\
	|| !env->stk->next->next->next->next->next->next->next->next	\
	|| !env->stk->next->next->next->next->next->next->next->next->next) \
    { execerror(env, "ten parameters", NAME); return; }
#define ONEQUOTE(NAME)							\
    if (env->stk->op != LIST_)						\
    { execerror(env, "quotation as top parameter", NAME); return; }
#define TWOQUOTES(NAME)							\
    ONEQUOTE(NAME);							\
    if (env->stk->next->op != LIST_)					\
    { execerror(env, "quotation as second parameter", NAME); return; }
#define THREEQUOTES(NAME)						\
    TWOQUOTES(NAME);							\
    if (env->stk->next->next->op != LIST_)				\
    { execerror(env, "quotation as third parameter", NAME); return; }
#define FOURQUOTES(NAME)						\
    THREEQUOTES(NAME);							\
    if (env->stk->next->next->next->op != LIST_)			\
    { execerror(env, "quotation as fourth parameter", NAME); return; }
#define SAME2TYPES(NAME)						\
    if (env->stk->op != env->stk->next->op)				\
    { execerror(env, "two parameters of the same type", NAME); return; }
#define STRING(NAME)							\
    if (env->stk->op != STRING_ && env->stk->op != USR_)		\
    { execerror(env, "string", NAME); return; }
#define STRING2(NAME)							\
    if (env->stk->next->op != STRING_ && env->stk->op != USR_)		\
    { execerror(env, "string as second parameter", NAME); return; }
#define STRING3(NAME)							\
    if (env->stk->next->next->op != STRING_)				\
    { execerror(env, "string as third parameter", NAME); return; }
#define STRING4(NAME)							\
    if (env->stk->next->next->next->op != STRING_)			\
    { execerror(env, "string as fourth parameter", NAME); return; }
#define STRING5(NAME)							\
    if (env->stk->next->next->next->next->op != STRING_)		\
    { execerror(env, "string as fifth parameter", NAME); return; }
#define INTEGER(NAME)							\
    if (env->stk->op != INTEGER_)					\
    { execerror(env, "integer", NAME); return; }
#define INTEGER2(NAME)							\
    if (env->stk->next->op != INTEGER_)					\
    { execerror(env, "integer as second parameter", NAME); return; }
#define INTEGER3(NAME)							\
    if (env->stk->next->next->op != INTEGER_)				\
    { execerror(env, "integer as third parameter", NAME); return; }
#define INTEGER4(NAME)							\
    if (env->stk->next->next->next->op != INTEGER_)			\
    { execerror(env, "integer as fourth parameter", NAME); return; }
#define INTEGER5(NAME)							\
    if (env->stk->next->next->next->next->op != INTEGER_)		\
    { execerror(env, "integer as fifth parameter", NAME); return; }
#define INTEGER6(NAME)							\
    if (env->stk->next->next->next->next->next->op != INTEGER_)		\
    { execerror(env, "integer as sixth parameter", NAME); return; }
#define INTEGER7(NAME)							\
    if (env->stk->next->next->next->next->next->next->op != INTEGER_)	\
    { execerror(env, "integer as seventh parameter", NAME); return; }
#define INTEGER8(NAME)							\
    if (env->stk->next->next->next->next->next->next->next->op != INTEGER_) \
    { execerror(env, "integer as eighth parameter", NAME); return; }
#define INTEGER9(NAME)							\
    if (env->stk->next->next->next->next->next->next->next->next->op	\
	!= INTEGER_)							\
    { execerror(env, "integer as nineth parameter", NAME); return; }
#define INTEGER10(NAME)							\
    if (env->stk->next->next->next->next->next->next->next->next->next->op \
	!= INTEGER_)							\
    { execerror(env, "integer as tenth parameter", NAME); return; }
#define CHARACTER(NAME)							\
    if (env->stk->op != CHAR_)						\
    { execerror(env, "character", NAME); return; }
#define INTEGERS2(NAME)							\
    if (env->stk->op != INTEGER_ || env->stk->next->op != INTEGER_)	\
    { execerror(env, "two integers", NAME); return; }
#define NUMERICTYPE(NAME)						\
    if (env->stk->op != INTEGER_ && env->stk->op != CHAR_		\
	&& env->stk->op != BOOLEAN_)					\
    { execerror(env, "numeric", NAME); return; }
#define NUMERIC2(NAME)							\
    if (env->stk->next->op != INTEGER_ && env->stk->next->op != CHAR_)	\
    { execerror(env, "numeric second parameter", NAME); return; }
#define FLOAT(NAME)							\
    if (!FLOATABLE)							\
	{ execerror(env, "float or integer", NAME); return; }
#define FLOAT2(NAME)							\
    if (!(FLOATABLE2							\
	|| (env->stk->op == INTEGER_ && env->stk->next->op == INTEGER_))) \
    { execerror(env, "two floats or integers", NAME); return; }
#define FILE(NAME)							\
    if (env->stk->op != FILE_ || !env->stk->u.fil)			\
    { execerror(env, "file", NAME); return; }
#define CHECKZERO(NAME)							\
    if ((env->stk->op == FLOAT_ && !env->stk->u.dbl) ||			\
	(env->stk->op == INTEGER_ && !env->stk->u.num))			\
    { execerror(env, "non-zero operand", NAME); return; }
#define LIST(NAME)							\
    if (env->stk->op != LIST_)						\
    { execerror(env, "list", NAME); return; }
#define LIST2(NAME)							\
    if (env->stk->next->op != LIST_)					\
    { execerror(env, "list as second parameter", NAME); return; }
#define LIST3(NAME)							\
    if (env->stk->next->next->op != LIST_)				\
    { execerror(env, "list as third parameter", NAME); return; }
#define USERDEF(NAME)							\
    if (env->stk->op != USR_)						\
    { execerror(env, "user defined symbol", NAME); return; }
#define CHECKLIST(OPR, NAME)						\
    if (OPR != LIST_)							\
    { execerror(env, "internal list", NAME); return; }
#define CHECKSETMEMBER(NODE, NAME)					\
    if ((NODE->op != INTEGER_ && NODE->op != CHAR_)			\
	|| NODE->u.num >= SETSIZE_)					\
    { execerror(env, "small numeric", NAME); return; }
#define CHECKEMPTYSET(SET, NAME)					\
    if (!SET)								\
    { execerror(env, "non-empty set", NAME); return; }
#define CHECKEMPTYSTRING(STRING, NAME)					\
    if (!*STRING)							\
    { execerror(env, "non-empty string", NAME); return; }
#define CHECKEMPTYLIST(LIST, NAME)					\
    if (!LIST)								\
    { execerror(env, "non-empty list", NAME); return; }
#define CHECKCHARACTER(ELEM, NAME)					\
    if (ELEM->op != CHAR_)						\
    { execerror(env, "character", NAME); return; }
#define CHECKDIVISOR(NAME)						\
    if ((env->stk->op == FLOAT_ && !env->stk->u.dbl) ||			\
	(env->stk->op == INTEGER_ && !env->stk->u.num))			\
    { execerror(env, "non-zero divisor", NAME); return; }
#define CHECKFORMAT(SPEC, NAME)						\
    if (!strchr("dioxX", SPEC))						\
    { execerror(env, "one of: d i o x X", NAME); return; }
#define CHECKFORMATF(SPEC, NAME)					\
    if (!strchr("eEfgG", SPEC))						\
    { execerror(env, "one of: e E f g G", NAME); return; }
#define CHECKNUMERIC(ELEM, NAME)					\
    if (ELEM->op != INTEGER_ && ELEM->op != CHAR_ && ELEM->op != BOOLEAN_) \
    { execerror(env, "numeric list", NAME); return; }
#define CHECKNAME(ELEM, NAME)						\
    if (!ELEM || *ELEM)							\
    { execerror(env, "valid name", NAME); return; }
#define CHECKSTACK(NAME)						\
    if (!env->stk)							\
    { execerror(env, "non-empty stack", NAME); return; }
#define TWONUMBERS(NAME)						\
    if (((env->stk->op == FLOAT_ || env->stk->op == INTEGER_) &&	\
	(env->stk->next->op == FLOAT_ || env->stk->next->op == INTEGER_)) || \
	(env->stk->op == INTEGER_ && (env->stk->next->op == CHAR_ ||	\
	env->stk->next->op == INTEGER_)));				\
    else { execerror(env, "two floats or numerics", NAME); return; }
#define CHECKVALUE(NAME)						\
    if (!env->stk)							\
    { execerror(env, "value to push", NAME); return; }
#define POSITIVEINDEX(INDEX, NAME)					\
    if (INDEX->op != INTEGER_ || INDEX->u.num < 0)			\
    { execerror(env, "non-negative integer", NAME); return; }
#define INDEXTOOLARGE(NAME)  { execerror(env, "smaller index", NAME);	\
			       return; }
#define BADAGGREGATE(NAME)   { execerror(env, "aggregate parameter",	\
			       NAME); return; }
#define BADDATA(NAME)	     { execerror(env, "different type", NAME);	\
			       return; }

#define NULLARY(CONSTRUCTOR, VALUE)					\
    env->stk = CONSTRUCTOR(VALUE, env->stk)
#define UNARY(CONSTRUCTOR, VALUE)					\
    env->stk = CONSTRUCTOR(VALUE, env->stk->next)
#define BINARY(CONSTRUCTOR, VALUE)					\
    env->stk = CONSTRUCTOR(VALUE, env->stk->next->next)
#define GNULLARY(TYPE, VALUE)						\
    env->stk = newnode(TYPE, VALUE, env->stk)
#define GUNARY(TYPE, VALUE)						\
    env->stk = newnode(TYPE, VALUE, env->stk->next)
#define GBINARY(TYPE, VALUE)						\
    env->stk = newnode(TYPE, VALUE, env->stk->next->next)
#define GTERNARY(TYPE, VALUE)						\
    env->stk = newnode(TYPE, VALUE, env->stk->next->next->next)
#endif
