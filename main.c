/*
    module  : main.c
    version : 1.4
    date    : 04/22/17
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include "joy.h"
#include "symbol.h"

static jmp_buf begin;

void execerror(char *message, const char *op)
{
    if (!strncmp(op, "do_", 3))
	op += 3;
    fprintf(stderr, "run time error: %s needed for %s\n", message, op);
    longjmp(begin, 1);
}

int main(int argc, char **argv)
{
    char *file;

    initsym(argc, argv);
    if (argc > 1) {
	g_argc--;
	g_argv++;
	if (!strcmp(file = argv[1], "-c"))
	    compiling = 1;
	else if (!strcmp(argv[1], "-o"))
	    compiling = optimizing = 1;
	if (compiling) {
	    initialise();
	    file = argv[2];
	}
	if ((yyin = freopen(file, "r", stdin)) == 0) {
	    fprintf(stderr, "failed to open the file '%s'.\n", file);
	    return 1;
	}
    } else {
	printf("JOY  -  compiled at %s on %s (BDW)\n", __TIME__, __DATE__);
	printf("Copyright 2001 by Manfred von Thun\n");
    }
    setjmp(begin);
    argc = yyparse();
    if (compiling)
	finalise();
    return argc;
}
