/*
    module  : initsym.c
    version : 1.7
    date    : 06/28/18
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "joy.h"
#include "symbol.h"

#define MAXSTR		100

char **g_argv;
int g_argc, error;
clock_t startclock;
FILE *outfp, *declfp;
char *mainfunc;
unsigned debugging, compiling, optimizing, identifier;
unsigned autoput = 1, undeferror = 1, echoflag, tracegc;

void initsym(int argc, char **argv)
{
    char *ptr;
    int i, rv = 0;

    setbuf(stdout, 0);
    startclock = clock();
    if (argc > 1) {
	rv = 1;
	if (argv[1][0] == '-') {
	    rv = 2;
	    for (i = 1; argv[1][i]; i++)
		switch (argv[1][i]) {
		case 'c' : compiling = 1;
			   break;
		case 'd' : debugging = 1;
			   break;
		case 'o' : compiling = 1;
			   optimizing = 1;
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
    initmem();
    init_dict();
}
