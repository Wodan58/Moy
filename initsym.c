/*
    module  : initsym.c
    version : 1.15
    date    : 03/28/20
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
char **g_argv;
int g_argc, compiling, debugging, definition, interpreter, nologo;
int autoput = INIAUTOPUT, tracegc = INITRACEGC, undeferror = INIUNDEFERR;

static int is_interpreter(char *prog)
{
    int i;
    char str[4], *ptr;

    if ((ptr = strchr(prog, '/')) != 0)
	ptr++;
    else if ((ptr = strchr(prog, '\\')) != 0)
	ptr++;
    else
	ptr = prog;
    strncpy(str, ptr, 3);
    str[3] = 0;
    for (i = 0; i < 3; i++)
	str[i] = toupper(str[i]);
    return !strcmp(str, "JOY");
}

void initsym(int argc, char **argv)
{
    FILE *fp;
    char *ptr;
    int i, rv = 0;

    setbuf(stdout, 0);
    startclock = clock();
    setechoflag(INIECHOFLAG);
    inilinebuffer(stdin, "stdin");
    interpreter = is_interpreter(argv[0]);
    if (argc > 1) {
	rv = 1;
	if (argv[1][0] == '-') {
	    rv = 2;
	    for (i = 1; argv[1][i]; i++)
		switch (argv[1][i]) {
		case 'c' : compiling = 1;
			   initialise();
			   break;
		case 'd' : debugging = 1;
			   break;
		case 's' : nologo = 1;
			   break;
		}
	}
	ptr = argv[rv];
	if (!ptr || isdigit(*ptr))
	    rv--;
	else {
	    if ((fp = freopen(ptr, "r", stdin)) == 0) {
		fprintf(stderr, "failed to open the file '%s'.\n", ptr);
		exit(0);
	    }
	    inilinebuffer(fp, ptr);
	}
    }
    g_argc = argc - rv;
    g_argv = &argv[rv];
    init_dict();
    stk = 0;
}
