/*
    module  : main.c
    version : 1.16
    date    : 06/29/22
*/
#include "globals.h"

static jmp_buf begin;

/*
    Abort execution and resume main loop.
*/
void abortexecution(void)
{
    longjmp(begin, 1);
}

/*
    fatal terminates the program after a stack overflow, likely to result in
    heap corruption that makes it impossible to continue.
*/
#ifndef GC_BDW
void fatal(void)
{
    fflush(stdout);
    fprintf(stderr, "fatal error: memory overflow\n");
    exit(EXIT_FAILURE);
}
#endif

int start_main(int argc, char **argv)
{
    Env env; /* symbol table, stack, list, buckets */

    memset(&env, 0, sizeof(env)); /* this also initialises the stack */
    initsym(&env, argc, argv);
    if (setjmp(begin) && !interpreter)
	return 0;
    return yyparse(&env); /* main doesn't return */
}

int main(int argc, char **argv)
{
    int (*volatile m)(int, char **) = start_main;

#ifdef GC_BDW
    GC_INIT();
#else
    GC_init(&argc, fatal);
#endif
    return (*m)(argc, argv);
}
