/*
    module  : main.c
    version : 1.12
    date    : 07/06/19
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
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
    if (argc == 1 && isatty(fileno(stdin))) {
	printf("JOY  -  compiled at %s on %s (BDW)\n", __TIME__, __DATE__);
	printf("Copyright 2001 by Manfred von Thun\n");
    }
    initsym(argc, argv);
    if (compiling)
	initialise();
    setjmp(begin);
    return yyparse();
}
