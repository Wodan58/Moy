/*
 *  module  : read.c
 *  version : 1.12
 *  date    : 11/20/24
 */
#include "globals.h"

/*
 * readfactor - read a factor from srcfile and push it on the stack.
 */
int readfactor(pEnv env)	/* read a JOY factor */
{
    int index;
    Entry ent;
    Node node;
    uint64_t set = 0;

    switch (env->token) {
    case USR_:
	index = lookup(env, yylval.str);
	if (!index && strchr(yylval.str, '.')) {
	    yyerror(env, "no such field in module");
	    break;	/* LCOV_EXCL_LINE */
	}
	ent = vec_at(env->symtab, index);
	/* do not execute immediate functions at compile time */
	if (ent.is_user) {
	    node.u.ent = index;
	    node.op = USR_;
	} else {
	    node.u.proc = ent.u.proc;
	    node.op = ANON_FUNCT_;
	}
	vec_push(env->stck, node);
	return 1;

    case CHAR_:
    case INTEGER_:
    case STRING_:
    case FLOAT_:
    case BIGNUM_:
	node.u = yylval;
	node.op = env->token;
	vec_push(env->stck, node);
	return 1;

    case '{':
	while ((env->token = yylex(env)) != '}')
	    if ((env->token != CHAR_ && env->token != INTEGER_)
		|| yylval.num < 0 || yylval.num >= SETSIZE)
		yyerror(env, "small numeric expected in set");
	    else
		set |= ((int64_t)1 << yylval.num);
	node.u.set = set;
	node.op = SET_;
	vec_push(env->stck, node);
	return 1;

    case '[':
	env->token = yylex(env);	/* read past [ */
	readterm(env);
	return 1;

    case '(':
	yyerror(env, "'(' not implemented");
	break;	/* LCOV_EXCL_LINE */

    default:
	yyerror(env, "a factor cannot begin with this symbol");
	break;	/* LCOV_EXCL_LINE */
    }
    return 0;
}

/*
 * readterm - read a term from srcfile and push this on the stack as a list.
 */
void readterm(pEnv env)
{
    Node node;

    vec_init(node.u.lis);
    node.op = LIST_;
    if (env->token != ']') {
	do {
	    if (readfactor(env))
		vec_push(node.u.lis, vec_pop(env->stck));
	} while ((env->token = yylex(env)) != ']');	/* read past factor */
	vec_push(node.u.lis, node);			/* add dummy node */
	vec_reverse(node.u.lis);			/* reverse */
    }
    vec_push(env->stck, node);
}
