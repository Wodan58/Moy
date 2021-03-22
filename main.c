/*
    module  : main.c
    version : 1.13
    date    : 03/15/21
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#ifdef GC_BDW
#include <gc.h>
#endif
#include "joy.h"
#include "symbol.h"

pEnv environment;	/* parse.y */

YYSTYPE bucket;

static jmp_buf begin;

void execerror(char *message, const char *op)
{
    if (message && op) {
	if (!strncmp(op, "do_", 3))
	    op += 3;
	fprintf(stderr, "run time error: %s needed for %s\n", message, op);
    }
    longjmp(begin, 1);
}

int start_main(int argc, char **argv)
{
    Env env; /* symbol table, stack, list */

    initsym(&env, argc, argv);
    if (argc == 1 && interpreter && !nologo) {
#ifdef GC_BDW
	printf("JOY  -  compiled at %s on %s (BDW)\n", __TIME__, __DATE__);
#else
	printf("JOY  -  compiled at %s on %s (MINGC)\n", __TIME__, __DATE__);
#endif
	printf("Copyright 2001 by Manfred von Thun\n");
    }
    if (setjmp(begin) && !interpreter)
	return 1;
    environment = &env;
    return yyparse();
}

int main(int argc, char **argv)
{
    int (*volatile m)(int, char **) = start_main;

#ifdef GC_BDW
    GC_INIT();
#else
    GC_init(&argc);
#endif
    return (*m)(argc, argv);
}
