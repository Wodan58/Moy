/*
    module  : scan.c
    version : 1.6
    date    : 08/17/20
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"
#include "decl.h"

extern FILE *yyin;
extern char line[];
extern int yylineno;

static int ilevel;

static struct {
    FILE *fp;
    char *name;
    int linenum;
} infile[INPSTACKMAX];

void inilinebuffer(FILE *fp, char *str)
{
    infile[0].fp = yyin = fp;
    infile[0].name = str;
    infile[0].linenum = 0;
}

void redirect(FILE *fp)
{
    if (infile[ilevel].fp == fp)
	return;
    infile[ilevel].linenum = yylineno;
    if (ilevel + 1 == INPSTACKMAX)
	execerror("fewer include files", "redirect");
    infile[++ilevel].fp = yyin = fp;
    infile[ilevel].name = 0;
    infile[ilevel].linenum = yylineno = 0;
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
    infile[ilevel].name = ck_strdup(filnam);
}

int yywrap(void)
{
    if (yyin != stdin)
	fclose(yyin);
    if (!ilevel)
	exit(0);
    yyin = infile[--ilevel].fp;
    yylineno = infile[ilevel].linenum;
    old_buffer();
    return 0;
}

int yyerror(char *str)
{
    fprintf(stderr, "%s in file %s line %d : ", str,
	    infile[ilevel].name, yylineno);
    fprintf(stderr, "%s\n", line);
    execerror(0, 0);
    return 0;
}
