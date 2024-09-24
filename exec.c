/*
 *  module  : exec.c
 *  version : 1.8
 *  date    : 09/17/24
 */
#include "globals.h"

/*
 * Execute a program and print the result according to the autoput settings,
 * if there is anything to be printed.
 */
void execute(pEnv env, NodeList list)
{
#ifdef BYTECODE
    if (env->bytecoding == 1) {
	bytecode(env, list);
	return;
    }
    if (env->compiling == 1) {
	compile(env, list);	/* this compiles source code */
	return;
    }
#endif
    evaluate(env, list);
    print(env);
}
