/*
 *  module  : read.c
 *  version : 1.10
 *  date    : 03/21/24
 */
#include "globals.h"

/*
    readfactor - read a factor from srcfile and push it on the stack.
*/
int readfactor(pEnv env) /* read a JOY factor */
{
    int index;
    Node node;
    Entry ent;
    uint64_t set = 0;

    switch (env->token) {
    case USR_:
	index = lookup(env, yylval.str);
	if (!index && strchr(yylval.str, '.')) {
	    yyerror(env, "no such field in module");
	    break;
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
	env->stck = pvec_add(env->stck, node);
	return 1;

    case CHAR_:
    case INTEGER_:
    case STRING_:
    case FLOAT_:
    case BIGNUM_:
	node.u = yylval;
	node.op = env->token;
	env->stck = pvec_add(env->stck, node);
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
	env->stck = pvec_add(env->stck, node);
	return 1;

    case '[':
	env->token = yylex(env); /* read past [ */
	readterm(env);
	return 1;

    case '(':
	yyerror(env, "'(' not implemented");
	break;

    default:
	yyerror(env, "a factor cannot begin with this symbol");
	break;
    }
    return 0;
}

/*
    readterm - read a term from srcfile and push this on the stack as a list.
	       The nodes are first collected in a vector and only afterwards
	       pushed as a NodeList.
*/
void readterm(pEnv env)
{
    int i;
    Node node, temp;
    vector(Node) *array;

    vec_init(array);	/* collect nodes in a vector */
    node.u.lis = 0;	/* initialize the NodeList */
    node.op = LIST_;
    if (env->token != ']') {
	do {
	    if (readfactor(env)) {
		env->stck = pvec_pop(env->stck, &temp);
		vec_push(array, temp);
	    }
	} while ((env->token = yylex(env)) != ']');	/* read past factor */
	node.u.lis = pvec_init();
	for (i = vec_size(array) - 1; i >= 0; i--)	/* reverse */
	    node.u.lis = pvec_add(node.u.lis, vec_at(array, i));
    }
    env->stck = pvec_add(env->stck, node);
}
