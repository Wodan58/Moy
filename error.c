/*
    module  : error.c
    version : 1.2
    date    : 07/02/18
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
