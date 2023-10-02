/*
 *  module  : exec.c
 *  version : 1.3
 *  date    : 10/02/23
 */
#include "globals.h"

/*
 *  Execute a program and print the result according to the autoput settings,
 *  if there is anything to be printed.
 */
PUBLIC void execute(pEnv env, NodeList *list)
{
    Node node;

#ifdef COMPILING
    if (env->compiling) {
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
	putchar('\n');
    }
}
