/*
    module  : scan.c
    version : 1.2
    date    : 03/18/17
*/
#include <stdio.h>
#include <ctype.h>
#include "joy.h"
#include "symbol.h"

#define INPSTACKMAX	10

static int ilevel;
static FILE *infile[INPSTACKMAX];

void redirect(FILE *fp)
{
    if (ilevel + 1 == INPSTACKMAX)
	execerror("fewer include files", "redirect");
    infile[ilevel++] = yyin;
    infile[ilevel] = yyin = fp;
    new_buffer();
}

void include(char *filnam)
{
    FILE *fp;

    while (isspace((int)*filnam))
	filnam++;
    if ((fp = fopen(filnam, "r")) == 0)
	execerror("valid file name", "include");
    redirect(fp);
}

int yywrap(void)
{
    if (yyin != stdin)
	fclose(yyin);
    if (!ilevel)
	return 1;
    yyin = infile[--ilevel];
    old_buffer();
    return 0;
}
