/*
 *  module  : print.c
 *  version : 1.1
 *  date    : 09/17/24
 */
#include "globals.h"

/*
 * print the stack according to the autoput settings.
 */
void print(pEnv env)
{
    Node node;

    if (vec_size(env->stck)) {
	if (env->autoput == 2)
	    writeterm(env, env->stck, stdout);
	else if (env->autoput == 1) {
	    node = vec_pop(env->stck);
	    if (node.op == LIST_) {
		putchar('[');
		writeterm(env, node.u.lis, stdout);
		putchar(']');
	    } else
		writefactor(env, node, stdout);
	}
	if (env->autoput) {
	    putchar('\n');
	    fflush(stdout);
	}
    }
}
