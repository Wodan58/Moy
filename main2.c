/*
    module  : main2.c
    version : 1.2
    date    : 09/09/16
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#define ALLOC
#include "globals1.h"

extern FILE *yyin, *yyout;

/* inisymboltable */
struct optable_t optable[1];

int joy_main();

PUBLIC void execerror(char *message, char *op)
{
    fprintf(stderr, "run time error: %s needed for %s\n", message, op);
    exit(1);
}

int main(int argc, char **argv)
{
    g_argc = argc;
    g_argv = argv;
    yyin = stdin;
    yyout = stdout;
    if (argc > 1 && !freopen(argv[1], "r", stdin)) {
	fprintf(stderr, "failed to open the file '%s'.\n", argv[1]);
	exit(1);
    }
    inilinebuffer();
    startclock = clock();
    correct_inhas_compare = 1;
    initmem();
    return joy_main();
}
