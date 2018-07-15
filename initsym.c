/*
    module  : initsym.c
    version : 1.10
    date    : 07/14/18
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
int g_argc, debugging, compiling, definition, new_version;
int autoput = INIAUTOPUT, tracegc = INITRACEGC, undeferror = INIUNDEFERR;

void initsym(int argc, char **argv)
{
    char *ptr;
    int i, rv = 0;

    setbuf(stdout, 0);
    startclock = clock();
    setechoflag(INIECHOFLAG);
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
		}
	    if (compiling && !strcmp(argv[2], "-f")) {
		rv = 4;
		mainfunc = argv[3];
	    }
	}
	ptr = argv[rv];
	if (!ptr || isdigit(*ptr))
	    rv--;
	else if ((yyin = freopen(ptr, "r", stdin)) == 0) {
	    fprintf(stderr, "failed to open the file '%s'.\n", ptr);
	    exit(1);
	}
    }
    g_argc = argc - rv;
    g_argv = &argv[rv];
    init_dict();
    stk = 0;
}
