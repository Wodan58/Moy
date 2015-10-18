/*
    module  : main1.c
    version : 1.1
    date    : 10/18/15
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <gc.h>
#define ALLOC
#include "globals.h"

extern FILE *yyin, *yyout;

jmp_buf begin;

PUBLIC void abortexecution_(void)
{
    longjmp(begin, 1);
}

PUBLIC void execerror(char *message, char *op)
{
    printf("run time error: %s needed for %s\n", message, op);
    abortexecution_();
}

PUBLIC void quit_(void)
{
    exit(0);
}

int main(int argc, char **argv)
{
    FILE *fp;

    GC_init();
    g_argc = argc;
    g_argv = argv;
    if (argc > 1) {
	g_argc--;
	g_argv++;
	yyin = fopen(argv[1], "r");
	if (!yyin) {
	    printf("failed to open the file '%s'.\n", argv[1]);
	    exit(1);
	}
	inilinebuffer(argv[1]);
    } else {
	printf("MOY  -  compiled at %s on %s (BDW)\n", __TIME__, __DATE__);
	printf("Copyright 2001 by Manfred von Thun\n");
	yyin = stdin;
	inilinebuffer(0);
    }
    startclock = clock();
    echoflag = INIECHOFLAG;
    tracegc = INITRACEGC;
    autoput = INIAUTOPUT;
    inisymboltable();
    if ((fp = fopen("usrlib.joy", "r")) != 0) {
	fclose(fp);
	doinclude("usrlib.joy");
    }
    setbuf(yyout = stdout, 0);
    setjmp(begin);
    return yyparse();
}
