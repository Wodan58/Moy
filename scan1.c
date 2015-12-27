/*
    module  : scan1.c
    version : 1.2
    date    : 12/27/15
*/
#include <stdio.h>
#include <stdlib.h>
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
    infile[++ilevel] = yyin = fp;
}

PUBLIC void doinclude(char *filnam)
{
    FILE *fp;

    if ((fp = fopen(filnam, "r")) == 0)
	execerror("valid file name", "include");
    redirect(fp);
}

int yywrap()
{
    if (yyin != stdin)
	fclose(yyin);
    if (!ilevel)
	return 1;
    yyin = infile[--ilevel];
    return 0;
}
