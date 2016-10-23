/*
    module  : scan1.c
    version : 1.3
    date    : 10/04/16
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "globals1.h"

extern FILE *yyin;

static int ilevel;
static FILE *infile[INPSTACKMAX];

PUBLIC void inilinebuffer(void)
{
    infile[0] = yyin;
}

PUBLIC void redirect(FILE *fp)
{
    if (ilevel + 1 == INPSTACKMAX)
	execerror("fewer include files", "redirect");
    infile[ilevel++] = yyin;
    infile[ilevel] = yyin = fp;
}

PUBLIC void include(char *filnam)
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
    return 0;
}
