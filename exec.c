/*
 *  module  : exec.c
 *  version : 1.7
 *  date    : 04/11/24
 */
#include "globals.h"

/*
 * Execute a program and print the result according to the autoput settings,
 * if there is anything to be printed.
 */
void execute(pEnv env, NodeList *list)
{
    Node node;

#ifdef BYTECODE
    if (env->bytecoding == 1) {
	bytecode(env, list);
	return;
    }
#endif
    evaluate(env, list);
    if (pvec_cnt(env->stck)) {
	if (env->autoput == 2)
	    writeterm(env, env->stck, stdout);
	else if (env->autoput == 1) {
	    env->stck = pvec_pop(env->stck, &node);
	    if (node.op == LIST_) {
		putchar('[');
		writeterm(env, node.u.lis, stdout);
		putchar(']');
	    } else
		writefactor(env, node, stdout);
	}
	if (env->autoput)
	    putchar('\n');
    }
}
