/*
    module  : get.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef GET_C
#define GET_C

/**
Q0  OK  3070  get  :  A  ->  F
[IMPURE] Reads a factor from input and pushes it onto stack.
*/
PRIVATE void get_(pEnv env)
{
    Node node;

    if (env->ignore) {
	node.u.num = 0;
	node.op = INTEGER_;
	env->stck = pvec_add(env->stck, node);
	return;
    }
    env->token = yylex(env);
    readfactor(env);
}
#endif
