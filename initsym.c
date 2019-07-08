/*
    module  : initsym.c
    version : 1.14
    date    : 06/16/19
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "joy.h"
#include "symbol.h"
#include "decl.h"

clock_t startclock;
FILE *outfp, *declfp;
char **g_argv, *mainfunc;
int g_argc, debugging, compiling, definition, new_version, old_version;
int autoput = INIAUTOPUT, tracegc = INITRACEGC, undeferror = INIUNDEFERR;

void initsym(int argc, char **argv)
{
    FILE *fp;
    char *ptr;
    int i, rv = 0;

    setbuf(stdout, 0);
    startclock = clock();
#ifndef WITHOUT_YYLEX
    setechoflag(INIECHOFLAG);
    inilinebuffer(stdin, "stdin");
#endif
    if (argc > 1) {
	rv = 1;
	if (argv[1][0] == '-') {
	    rv = 2;
	    for (i = 1; argv[1][i]; i++)
		switch (argv[1][i]) {
		case 'c' : compiling = new_version = 1;
			   break;
		case 'd' : debugging = 1;
			   break;
		case 'o' : compiling = 1;
			   break;
		case 'r' : compiling = old_version = 1;
			   break;
		}
	    if (compiling && !strcmp(argv[2], "-f")) {
		rv = 4;
		mainfunc = argv[3];
	    }
	}
	ptr = argv[rv];
	if (!ptr || isdigit(*ptr))
	    rv--;
#ifndef WITHOUT_YYLEX
	else {
	    if ((fp = freopen(ptr, "r", stdin)) == 0) {
		fprintf(stderr, "failed to open the file '%s'.\n", ptr);
		exit(1);
	    }
	    inilinebuffer(fp, ptr);
	}
#endif
    }
    g_argc = argc - rv;
    g_argv = &argv[rv];
    init_dict();
    stk = 0;
}
