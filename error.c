/*
    module  : error.c
    version : 1.3
    date    : 07/05/18
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void execerror(char *message, const char *op)
{
    if (!strncmp(op, "do_", 3))
	op += 3;
    fprintf(stderr, "run time error: %s needed for %s\n", message, op);
    exit(1);
}
