/*
 *  module  : exec.c
 *  version : 1.6
 *  date    : 03/21/24
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
	bytecode(list);
	return;
    }
#endif
#ifdef COMPILER
    if (env->compiling == 1) {
	compileprog(env, list);
	return;
    }
#endif
    exeterm(env, list);
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
