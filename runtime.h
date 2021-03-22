/*
    module  : runtime.h
    version : 1.18
    date    : 03/15/21
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

typedef struct table_t {
    proc_t proc;
    char *name;
} table_t;

extern table_t table[];
extern clock_t startclock;

#ifndef OLD_RUNTIME
#define COMPILE                                                                \
    if (compiling) {                                                           \
        printstack(env, outfp);                                                \
        fprintf(outfp, "%s(env);", __func__);                                  \
        return;                                                                \
    }
#endif

#define PRIVATE

#define exeterm(e, x) interprete(e, x)
#define POP(x) (x) = (x)->next;
#define DUPLICATE(x) env->stk = newnode((x)->op, (x)->u, env->stk);
#define PUSH_NUM(x, y)                                                         \
do { YYSTYPE u; u.num = (y); env->stk = newnode((x), u, env->stk); } while (0)
#define PUSH_PTR(x, y)                                                         \
do { YYSTYPE u; u.ptr = (y); env->stk = newnode((x), u, env->stk); } while (0)
#define PUSH_DBL(x) env->stk = dblnode((x), env->stk);
#define FLOATVAL                                                               \
    (env->stk->op == FLOAT_ ? env->stk->u.dbl : (double)env->stk->u.num)
#define FLOATVAL2                                                              \
    (env->stk->next->op == FLOAT_ ? env->stk->next->u.dbl                      \
                                  : (double)env->stk->next->u.num)

#ifdef NCHECK
#define FLOATABLE
#define FLOATABLE2
#define ONEPARAM(NAME)
#define TWOPARAMS(NAME)
#define THREEPARAMS(NAME)
#define FOURPARAMS(NAME)
#define FIVEPARAMS(NAME)
#define ONEQUOTE(NAME)
#define TWOQUOTES(NAME)
#define THREEQUOTES(NAME)
#define FOURQUOTES(NAME)
#define SAME2TYPES(NAME)
#define STRING(NAME)
#define STRING2(NAME)
#define INTEGER(NAME)
#define INTEGER2(NAME)
#define CHARACTER(NAME)
#define INTEGERS2(NAME)
#define NUMERICTYPE(NAME)
#define NUMERIC2(NAME)
#define FLOAT(NAME)
#define FLOAT2(NAME)
#define FILE(NAME)
#define CHECKZERO(NAME)
#define LIST(NAME)
#define LIST2(NAME)
#define USERDEF(NAME)
#define CHECKLIST(OPR, NAME)
#define CHECKSETMEMBER(NODE, NAME)
#define CHECKEMPTYSET(SET, NAME)
#define CHECKEMPTYSTRING(STRING, NAME)
#define CHECKEMPTYLIST(LIST, NAME)
#define INDEXTOOLARGE(NAME)
#define BADAGGREGATE(NAME)
#define BADDATA(NAME)
#else
#define FLOATABLE (env->stk->op == INTEGER_ || env->stk->op == FLOAT_)
#define FLOATABLE2                                                             \
    ((env->stk->op == FLOAT_ && env->stk->next->op == FLOAT_)                  \
        || (env->stk->op == FLOAT_ && env->stk->next->op == INTEGER_)          \
        || (env->stk->op == INTEGER_ && env->stk->next->op == FLOAT_))
#define ONEPARAM(NAME)                                                         \
    if (!env->stk)                                                             \
    execerror("one parameter", NAME)
#define TWOPARAMS(NAME)                                                        \
    if (!env->stk || !env->stk->next)                                          \
    execerror("two parameters", NAME)
#define THREEPARAMS(NAME)                                                      \
    if (!env->stk || !env->stk->next || !env->stk->next->next)                 \
    execerror("three parameters", NAME)
#define FOURPARAMS(NAME)                                                       \
    if (!env->stk || !env->stk->next || !env->stk->next->next                  \
        || !env->stk->next->next->next)                                        \
    execerror("four parameters", NAME)
#define FIVEPARAMS(NAME)                                                       \
    if (!env->stk || !env->stk->next || !env->stk->next->next                  \
        || !env->stk->next->next->next || !env->stk->next->next->next->next)   \
    execerror("five parameters", NAME)
#define ONEQUOTE(NAME)                                                         \
    if (env->stk->op != LIST_)                                                 \
    execerror("quotation as top parameter", NAME)
#define TWOQUOTES(NAME)                                                        \
    ONEQUOTE(NAME);                                                            \
    if (env->stk->next->op != LIST_)                                           \
    execerror("quotation as second parameter", NAME)
#define THREEQUOTES(NAME)                                                      \
    TWOQUOTES(NAME);                                                           \
    if (env->stk->next->next->op != LIST_)                                     \
    execerror("quotation as third parameter", NAME)
#define FOURQUOTES(NAME)                                                       \
    THREEQUOTES(NAME);                                                         \
    if (env->stk->next->next->next->op != LIST_)                               \
    execerror("quotation as fourth parameter", NAME)
#define SAME2TYPES(NAME)                                                       \
    if (env->stk->op != env->stk->next->op)                                    \
    execerror("two parameters of the same type", NAME)
#define STRING(NAME)                                                           \
    if (env->stk->op != STRING_)                                               \
    execerror("string", NAME)
#define STRING2(NAME)                                                          \
    if (env->stk->next->op != STRING_)                                         \
    execerror("string as second parameter", NAME)
#define INTEGER(NAME)                                                          \
    if (env->stk->op != INTEGER_)                                              \
    execerror("integer", NAME)
#define INTEGER2(NAME)                                                         \
    if (env->stk->next->op != INTEGER_)                                        \
    execerror("integer as second parameter", NAME)
#define CHARACTER(NAME)                                                        \
    if (env->stk->op != CHAR_)                                                 \
    execerror("character", NAME)
#define INTEGERS2(NAME)                                                        \
    if (env->stk->op != INTEGER_ || env->stk->next->op != INTEGER_)            \
    execerror("two integers", NAME)
#define NUMERICTYPE(NAME)                                                      \
    if (env->stk->op != INTEGER_ && env->stk->op != CHAR_                      \
        && env->stk->op != BOOLEAN_)                                           \
    execerror("numeric", NAME)
#define NUMERIC2(NAME)                                                         \
    if (env->stk->next->op != INTEGER_ && env->stk->next->op != CHAR_)         \
    execerror("numeric second parameter", NAME)
#define FLOAT(NAME)                                                            \
    if (!FLOATABLE)                                                            \
        execerror("float or integer", NAME);
#define FLOAT2(NAME)                                                           \
    if (!(FLOATABLE2                                                           \
            || (env->stk->op == INTEGER_ && env->stk->next->op == INTEGER_)))  \
    execerror("two floats or integers", NAME)
#define FILE(NAME)                                                             \
    if (env->stk->op != FILE_ || !env->stk->u.fil)                             \
    execerror("file", NAME)
#define CHECKZERO(NAME)                                                        \
    if (!env->stk->u.num)                                                      \
    execerror("non-zero operand", NAME)
#define LIST(NAME)                                                             \
    if (env->stk->op != LIST_)                                                 \
    execerror("list", NAME)
#define LIST2(NAME)                                                            \
    if (env->stk->next->op != LIST_)                                           \
    execerror("list as second parameter", NAME)
#define USERDEF(NAME)                                                          \
    if (env->stk->op != USR_)                                                  \
    execerror("user defined symbol", NAME)
#define CHECKLIST(OPR, NAME)                                                   \
    if (OPR != LIST_)                                                          \
    execerror("internal list", NAME)
#define CHECKSETMEMBER(NODE, NAME)                                             \
    if ((NODE->op != INTEGER_ && NODE->op != CHAR_)                            \
        || NODE->u.num >= SETSIZE_)                                            \
    execerror("small numeric", NAME)
#define CHECKEMPTYSET(SET, NAME)                                               \
    if (!SET)                                                                  \
    execerror("non-empty set", NAME)
#define CHECKEMPTYSTRING(STRING, NAME)                                         \
    if (!*STRING)                                                              \
    execerror("non-empty string", NAME)
#define CHECKEMPTYLIST(LIST, NAME)                                             \
    if (!LIST)                                                                 \
    execerror("non-empty list", NAME)
#define INDEXTOOLARGE(NAME) execerror("smaller index", NAME)
#define BADAGGREGATE(NAME) execerror("aggregate parameter", NAME)
#define BADDATA(NAME) execerror("different type", NAME)
#endif

#define NULLARY(CONSTRUCTOR, VALUE) env->stk = CONSTRUCTOR(VALUE, env->stk)
#define UNARY(CONSTRUCTOR, VALUE) env->stk = CONSTRUCTOR(VALUE, env->stk->next)
#define BINARY(CONSTRUCTOR, VALUE)                                             \
    env->stk = CONSTRUCTOR(VALUE, env->stk->next->next)
#define GNULLARY(TYPE, VALUE) env->stk = newnode(TYPE, VALUE, env->stk)
#define GUNARY(TYPE, VALUE) env->stk = newnode(TYPE, VALUE, env->stk->next)
#define GBINARY(TYPE, VALUE)                                                   \
    env->stk = newnode(TYPE, VALUE, env->stk->next->next)
#define GTERNARY(TYPE, VALUE)                                                  \
    env->stk = newnode(TYPE, VALUE, env->stk->next->next->next)

#define PARAM_1(arg) (env->stk && (arg))
#define PARAM_2(arg) (env->stk && env->stk->next && (arg))
#define PARAM_3(arg)                                                           \
    (env->stk && env->stk->next && env->stk->next->next && (arg))
#define PARAM_4(arg)                                                           \
    (env->stk && env->stk->next && env->stk->next->next                        \
        && env->stk->next->next->next && (arg))

#define NUMERIC_1 (PARAM_1(env->stk->op == INTEGER_ || env->stk->op == FLOAT_))
#define NUMERIC_2                                                              \
    (PARAM_2(env->stk->next->op == INTEGER_ || env->stk->next->op == FLOAT_))
#define NUMERIC_3                                                              \
    (PARAM_3(env->stk->next->next->op == INTEGER_                              \
        || env->stk->next->next->op == FLOAT_))
#define NUMERIC_4                                                              \
    (PARAM_4(env->stk->next->next->next->op == INTEGER_                        \
        || env->stk->next->next->next->op == FLOAT_))

#define FLOAT_1 (PARAM_1(env->stk->op == FLOAT_))
#define FLOAT_2 (PARAM_2(env->stk->next->op == FLOAT_))
#define FLOAT_3 (PARAM_3(env->stk->next->next->op == FLOAT_))
#define FLOAT_4 (PARAM_4(env->stk->next->next->next->op == FLOAT_))

#define INTEGER_1 (PARAM_1(env->stk->op == INTEGER_))
#define INTEGER_2 (PARAM_2(env->stk->next->op == INTEGER_))
#define INTEGER_3 (PARAM_3(env->stk->next->next->op == INTEGER_))
#define INTEGER_4 (PARAM_4(env->stk->next->next->next->op == INTEGER_))

#define CHAR_1 (PARAM_1(env->stk->op == CHAR_))
#define CHAR_2 (PARAM_2(env->stk->next->op == CHAR_))
#define CHAR_3 (PARAM_3(env->stk->next->next->op == CHAR_))
#define CHAR_4 (PARAM_4(env->stk->next->next->next->op == CHAR_))

#define BOOLEAN_1 (PARAM_1(env->stk->op == BOOLEAN_))
#define BOOLEAN_2 (PARAM_2(env->stk->next->op == BOOLEAN_))
#define BOOLEAN_3 (PARAM_3(env->stk->next->next->op == BOOLEAN_))
#define BOOLEAN_4 (PARAM_4(env->stk->next->next->next->op == BOOLEAN_))

#define STRING_1 (PARAM_1(env->stk->op == STRING_))
#define STRING_2 (PARAM_2(env->stk->next->op == STRING_))
#define STRING_3 (PARAM_3(env->stk->next->next->op == STRING_))
#define STRING_4 (PARAM_4(env->stk->next->next->next->op == STRING_))

#define SET_1 (PARAM_1(env->stk->op == SET_))
#define SET_2 (PARAM_2(env->stk->next->op == SET_))
#define SET_3 (PARAM_3(env->stk->next->next->op == SET_))
#define SET_4 (PARAM_4(env->stk->next->next->next->op == SET_))

#define LIST_1 (PARAM_1(env->stk->op == LIST_))
#define LIST_2 (PARAM_2(env->stk->next->op == LIST_))
#define LIST_3 (PARAM_3(env->stk->next->next->op == LIST_))
#define LIST_4 (PARAM_4(env->stk->next->next->next->op == LIST_))

#define VALID_1 (PARAM_1(env->stk->op))
#define VALID_2 (PARAM_2(env->stk->next->op))
#define VALID_3 (PARAM_3(env->stk->next->next->op))
#define VALID_4 (PARAM_4(env->stk->next->next->next->op))

#define AGGREGATE_1 (PARAM_1(env->stk->op >= SET_ && env->stk->op <= LIST_))
#define AGGREGATE_2                                                            \
    (PARAM_2(env->stk->next->op >= SET_ && env->stk->next->op <= LIST_))
#define AGGREGATE_3                                                            \
    (PARAM_3(env->stk->next->next->op >= SET_                                  \
        && env->stk->next->next->op <= LIST_))
#define AGGREGATE_4                                                            \
    (PARAM_4(env->stk->next->next->next->op >= SET_                            \
        && env->stk->next->next->next->op <= LIST_))
#endif
