/*
    module  : runtime.h
    version : 1.11
    date    : 07/02/18
*/
#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "joy.h"
#include "symbol.h"
#include "builtin.h"
#include "decl.h"

extern clock_t startclock;

#ifndef NCHECK
#define COMPILE		if (compiling) { printstack(outfp); \
			fprintf(outfp, "%s();", __func__); return; }
#endif

#define PRIVATE
#define INSIDE		0
#define OUTSIDE		1
#define CONDITION
#define RELEASE

#define exeterm(x)	interprete(x)
#define POP(x)		(x) = (x)->next
#define DUPLICATE(x)	do { \
			    if (OUTSIDE && INSIDE) { \
				stk[1].op = (x)->op; \
				stk[1].u = (x)->u; \
				++stk; \
			    } else \
				stk = newnode((x)->op, (x)->u.ptr, stk); \
			} while (0)
#define PUSH(x,y)	do { \
			    Node temp; \
			    temp.op = (x); \
			    temp.u.ptr = (void *)(y); \
			    DUPLICATE(&temp); \
			} while (0)
#define DBL_PUSH(x)	do { \
			    Node temp; \
			    temp.op = FLOAT_; \
			    temp.u.dbl = (x); \
			    DUPLICATE(&temp); \
			} while (0)
#define FLOATVAL	(stk->op == FLOAT_ ? stk->u.dbl : (double)stk->u.num)
#define FLOATVAL2	\
	(stk->next->op == FLOAT_ ? stk->next->u.dbl : (double)stk->next->u.num)

#define FLOATABLE						\
    (stk->op == INTEGER_ || stk->op == FLOAT_)
#define FLOATABLE2						\
    ((stk->op == FLOAT_ && stk->next->op == FLOAT_) ||		\
     (stk->op == FLOAT_ && stk->next->op == INTEGER_) ||	\
     (stk->op == INTEGER_ && stk->next->op == FLOAT_))
#define ONEPARAM(NAME)						\
    if (!stk)							\
	execerror("one parameter",NAME)
#define TWOPARAMS(NAME)						\
    if (!stk || !stk->next)					\
	execerror("two parameters",NAME)
#define THREEPARAMS(NAME)					\
    if (!stk || !stk->next					\
	     || !stk->next->next)				\
	execerror("three parameters",NAME)
#define FOURPARAMS(NAME)					\
    if (!stk || !stk->next					\
	     || !stk->next->next				\
	     || !stk->next->next->next)				\
	execerror("four parameters",NAME)
#define FIVEPARAMS(NAME)					\
    if (!stk || !stk->next					\
	     || !stk->next->next				\
	     || !stk->next->next->next				\
	     || !stk->next->next->next->next)			\
	execerror("five parameters",NAME)
#define ONEQUOTE(NAME)						\
    if (stk->op != LIST_)					\
	execerror("quotation as top parameter",NAME)
#define TWOQUOTES(NAME)						\
    ONEQUOTE(NAME);						\
    if (stk->next->op != LIST_)					\
	execerror("quotation as second parameter",NAME)
#define THREEQUOTES(NAME)					\
    TWOQUOTES(NAME);						\
    if (stk->next->next->op != LIST_)				\
	execerror("quotation as third parameter",NAME)
#define FOURQUOTES(NAME)					\
    THREEQUOTES(NAME);						\
    if (stk->next->next->next->op != LIST_)			\
	execerror("quotation as fourth parameter",NAME)
#define SAME2TYPES(NAME)					\
    if (stk->op != stk->next->op)				\
	execerror("two parameters of the same type",NAME)
#define STRING(NAME)						\
    if (stk->op != STRING_)					\
	execerror("string",NAME)
#define STRING2(NAME)						\
    if (stk->next->op != STRING_)				\
	execerror("string as second parameter",NAME)
#define INTEGER(NAME)						\
    if (stk->op != INTEGER_)					\
	execerror("integer",NAME)
#define INTEGER2(NAME)						\
    if (stk->next->op != INTEGER_)				\
	execerror("integer as second parameter",NAME)
#define CHARACTER(NAME)						\
    if (stk->op != CHAR_)					\
	execerror("character",NAME)
#define INTEGERS2(NAME)						\
    if (stk->op != INTEGER_ || stk->next->op != INTEGER_)	\
	execerror("two integers",NAME)
#define NUMERICTYPE(NAME)					\
    if (stk->op != INTEGER_ && stk->op != CHAR_			\
			    && stk->op != BOOLEAN_)		\
	execerror("numeric",NAME)
#define NUMERIC2(NAME)						\
    if (stk->next->op != INTEGER_ && stk->next->op != CHAR_)	\
	execerror("numeric second parameter",NAME)
#define FLOAT(NAME)						\
    if (!FLOATABLE)						\
	execerror("float or integer",NAME);
#define FLOAT2(NAME)						\
    if (!(FLOATABLE2 || (stk->op == INTEGER_ &&			\
			 stk->next->op == INTEGER_)))		\
	execerror("two floats or integers",NAME)
#define FILE(NAME)						\
    if (stk->op != FILE_ || !stk->u.fil)			\
	execerror("file",NAME)
#define CHECKZERO(NAME)						\
    if (!stk->u.num)						\
	execerror("non-zero operand",NAME)
#define LIST(NAME)						\
    if (stk->op != LIST_)					\
	execerror("list",NAME)
#define LIST2(NAME)						\
    if (stk->next->op != LIST_)					\
	execerror("list as second parameter",NAME)
#define USERDEF(NAME)						\
    if (stk->op != USR_)					\
	execerror("user defined symbol",NAME)
#define CHECKLIST(OPR,NAME)					\
    if (OPR != LIST_)						\
	execerror("internal list",NAME)
#define CHECKSETMEMBER(NODE,NAME)				\
    if ((NODE->op != INTEGER_ && NODE->op != CHAR_) ||		\
	NODE->u.num >= SETSIZE_)				\
	execerror("small numeric",NAME)
#define CHECKEMPTYSET(SET,NAME)					\
    if (!SET)							\
	execerror("non-empty set",NAME)
#define CHECKEMPTYSTRING(STRING,NAME)				\
    if (!*STRING)						\
	execerror("non-empty string",NAME)
#define CHECKEMPTYLIST(LIST,NAME)				\
    if (!LIST)							\
	execerror("non-empty list",NAME)
#define INDEXTOOLARGE(NAME)					\
    execerror("smaller index",NAME)
#define BADAGGREGATE(NAME)					\
    execerror("aggregate parameter",NAME)
#define BADDATA(NAME)						\
    execerror("different type",NAME)

#define USR_NEWNODE(u,r)	newnode(USR_, (void *)(u), r)
#define ANON_FUNCT_NEWNODE(u,r)	newnode(ANON_FUNCT_, (void *)(u), r)
#define BOOLEAN_NEWNODE(u,r)	newnode(BOOLEAN_, (void *)(long_t)(u), r)
#define CHAR_NEWNODE(u,r)	newnode(CHAR_, (void *)(long_t)(u), r)
#define INTEGER_NEWNODE(u,r)	newnode(INTEGER_, (void *)(long_t)(u), r)
#define SET_NEWNODE(u,r)	newnode(SET_, (void *)(ulong_t)(u), r)
#define STRING_NEWNODE(u,r)	newnode(STRING_, (void *)(u), r)
#define LIST_NEWNODE(u,r)	newnode(LIST_, (void *)(u), r)
#define FLOAT_NEWNODE(u,r)	dblnode((double)(u), r)
#define FILE_NEWNODE(u,r)	newnode(FILE_, (void *)(u), r)
#define SYM_NEWNODE(u,r)	newnode(SYMBOL_, (void *)(u), r)

#define NULLARY(CONSTRUCTOR,VALUE)                              \
    stk = CONSTRUCTOR(VALUE,stk)
#define UNARY(CONSTRUCTOR,VALUE)                                \
    stk = CONSTRUCTOR(VALUE,stk->next)
#define BINARY(CONSTRUCTOR,VALUE)                               \
    stk = CONSTRUCTOR(VALUE,stk->next->next)
#define GNULLARY(TYPE,VALUE)                                    \
    stk = newnode(TYPE,VALUE,stk)
#define GUNARY(TYPE,VALUE)                                      \
    stk = newnode(TYPE,VALUE,stk->next)
#define GBINARY(TYPE,VALUE)                                     \
    stk = newnode(TYPE,VALUE,stk->next->next)
#define GTERNARY(TYPE,VALUE)					\
    stk = newnode(TYPE,VALUE,stk->next->next->next)

#define PARAM_1(arg)	(stk && (arg))
#define PARAM_2(arg)	(stk && stk->next && (arg))
#define PARAM_3(arg)	(stk && stk->next && stk->next->next && (arg))
#define PARAM_4(arg)	(stk && stk->next && stk->next->next && \
			 stk->next->next->next && (arg))

#define NUMERIC_1	(PARAM_1(stk->op == INTEGER_ || stk->op == FLOAT_))
#define NUMERIC_2	(PARAM_2(stk->next->op == INTEGER_ || \
			 stk->next->op == FLOAT_))
#define NUMERIC_3	(PARAM_3(stk->next->next->op == INTEGER_ || \
			 stk->next->next->op == FLOAT_))
#define NUMERIC_4	(PARAM_4(stk->next->next->next->op == INTEGER_ || \
			 stk->next->next->next->op == FLOAT_))

#define FLOAT_1		(PARAM_1(stk->op == FLOAT_))
#define FLOAT_2		(PARAM_2(stk->next->op == FLOAT_))
#define FLOAT_3		(PARAM_3(stk->next->next->op == FLOAT_))
#define FLOAT_4		(PARAM_4(stk->next->next->next->op == FLOAT_))

#define INTEGER_1	(PARAM_1(stk->op == INTEGER_))
#define INTEGER_2	(PARAM_2(stk->next->op == INTEGER_))
#define INTEGER_3	(PARAM_3(stk->next->next->op == INTEGER_))
#define INTEGER_4	(PARAM_4(stk->next->next->next->op == INTEGER_))

#define CHAR_1		(PARAM_1(stk->op == CHAR_))
#define CHAR_2		(PARAM_2(stk->next->op == CHAR_))
#define CHAR_3		(PARAM_3(stk->next->next->op == CHAR_))
#define CHAR_4		(PARAM_4(stk->next->next->next->op == CHAR_))

#define BOOLEAN_1	(PARAM_1(stk->op == BOOLEAN_))
#define BOOLEAN_2	(PARAM_2(stk->next->op == BOOLEAN_))
#define BOOLEAN_3	(PARAM_3(stk->next->next->op == BOOLEAN_))
#define BOOLEAN_4	(PARAM_4(stk->next->next->next->op == BOOLEAN_))

#define STRING_1	(PARAM_1(stk->op == STRING_))
#define STRING_2	(PARAM_2(stk->next->op == STRING_))
#define STRING_3	(PARAM_3(stk->next->next->op == STRING_))
#define STRING_4	(PARAM_4(stk->next->next->next->op == STRING_))

#define SET_1		(PARAM_1(stk->op == SET_))
#define SET_2		(PARAM_2(stk->next->op == SET_))
#define SET_3		(PARAM_3(stk->next->next->op == SET_))
#define SET_4		(PARAM_4(stk->next->next->next->op == SET_))

#define LIST_1		(PARAM_1(stk->op == LIST_))
#define LIST_2		(PARAM_2(stk->next->op == LIST_))
#define LIST_3		(PARAM_3(stk->next->next->op == LIST_))
#define LIST_4		(PARAM_4(stk->next->next->next->op == LIST_))

#define VALID_1		(PARAM_1(stk->op))
#define VALID_2		(PARAM_2(stk->next->op))
#define VALID_3		(PARAM_3(stk->next->next->op))
#define VALID_4		(PARAM_4(stk->next->next->next->op))

#define AGGREGATE_1	(PARAM_1(stk->op >= SET_ && stk->op <= LIST_))
#define AGGREGATE_2	(PARAM_2(stk->next->op >= SET_ && \
			 stk->next->op <= LIST_))
#define AGGREGATE_3	(PARAM_3(stk->next->next->op >= SET_ && \
			 stk->next->next->op <= LIST_))
#define AGGREGATE_4	(PARAM_4(stk->next->next->next->op >= SET_ && \
			 stk->next->next->next->op <= LIST_))
#endif
