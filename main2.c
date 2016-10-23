/*
    module  : main2.c
    version : 1.5
    date    : 10/21/16
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#define ALLOC
#include "globals1.h"
#include "builtin.h"

extern FILE *yyin, *yyout;

/* inisymboltable */
struct optable_t optable[] = {
{"quit",	quit_,	"->",	" ", "Exit from Joy."},
{0, id_, "->", " ", "->"}
};

int identifier;

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
    inilinebuffer();
    startclock = clock();
    correct_inhas_compare = 1;
    initmem();
    return joy_main();
}
