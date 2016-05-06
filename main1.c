/*
    module  : main1.c
    version : 1.1
    date    : 04/23/16
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <gc.h>
#define ALLOC
#include "globals1.h"
#include "compile.h"

extern FILE *yyin, *yyout;

jmp_buf begin;
int compiling;

PUBLIC void execerror(char *message, char *op)
{
    fprintf(stderr, "run time error: %s needed for %s\n", message, op);
    longjmp(begin, 1);
}

int main(int argc, char **argv)
{
    int rv;
    char *file;

    GC_init();
    initmem();
    g_argc = argc;
    g_argv = argv;
    yyin = stdin;
    yyout = stdout;
    if (argc > 1) {
	g_argc--;
	g_argv++;
	compiling = !strcmp(argv[1], "-c");
	file = argv[compiling ? 2 : 1];
	if ((yyin = fopen(file, "r")) == 0) {
	    fprintf(stderr, "failed to open the file '%s'.\n", file);
	    exit(1);
	}
    } else {
	printf("JOY1.01  -  compiled at %s on %s (BDW)\n", __TIME__, __DATE__);
	printf("Copyright 2001 by Manfred von Thun\n");
    }
    inilinebuffer();
    setbuf(yyout, 0);
    setmode(fileno(yyout), O_BINARY);
    startclock = clock();
    echoflag = INIECHOFLAG;
    tracegc = INITRACEGC;
    autoput = INIAUTOPUT;
    inisymboltable();
    if (compiling)
	initcompile();
    setjmp(begin);
    stk = &memory[MEMORYMAX];
    rv = yyparse();
    if (compiling)
	exitcompile();
    return rv;
}
