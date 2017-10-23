/*
    module  : error.c
    version : 1.1
    date    : 03/12/17
*/
#include "runtime.h"

YYSTYPE yylval;

void execerror(char *message, const char *op)
{
    if (!strncmp(op, "do_", 3))
	op += 3;
    fprintf(stderr, "run time error: %s needed for %s\n", message, op);
    exit(1);
}
