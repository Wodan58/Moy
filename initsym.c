/*
    module  : initsym.c
    version : 1.6
    date    : 06/25/18
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

static void quit(void)
{
    exit(0);
}

#ifndef _MSC_VER
static char *name(char *str)
{
    if (!strcmp(str, "plus"))
	return "+";
    if (!strcmp(str, "minus"))
	return "-";
    if (!strcmp(str, "mul"))
	return "*";
    if (!strcmp(str, "divide"))
	return "/";
    if (!strcmp(str, "geql"))
	return ">=";
    if (!strcmp(str, "greater"))
	return ">";
    if (!strcmp(str, "leql"))
	return "<=";
    if (!strcmp(str, "less"))
	return "<";
    if (!strcmp(str, "neql"))
	return "!=";
    if (!strcmp(str, "eql"))
	return "=";
    return str;
}
#endif

void initsym(int argc, char **argv)
{
    char *ptr;
    Entry *sym;
    int rv = 0;
#ifndef _MSC_VER
    FILE *fp;
    unsigned adr;
    char chr, str[MAXSTR], cmd[MAXSTR], *tmp;
#endif

    startclock = clock();
    if (argc > 1) {
	rv = 1;
	if (argv[1][0] == '-') {
	    rv = 2;
	    switch (argv[1][1]) {
	    case 'c' : compiling = 1; break;
	    case 'd' : debugging = 1; break;
	    case 'o' : compiling = 1; optimizing = 1; break;
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
    sym = lookup("quit");
    sym->u.proc = quit;
    sym->flags |= IS_BUILTIN;
#ifndef _MSC_VER
    if (!argv)
	return;
    sprintf(str, "%s.sym", argv[0]);
    if ((fp = fopen(str, "r")) == 0)
	return;
    while (fscanf(fp, "%x %c %s", &adr, &chr, str) == 3) {
	ptr = name(str + 4);
	if ((tmp = strchr(ptr, '.')) != 0)
	    *tmp = 0;
	sym = lookup(ptr);
	if (sym->flags & IS_BUILTIN)
	    sym = lookup(str + 3);
	sym->u.proc = (void (*)(void))adr;
	sym->flags = IS_BUILTIN;
    }
    fclose(fp);
#endif
}
