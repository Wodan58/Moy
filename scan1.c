/*
    module  : scan1.c
    version : 1.1
    date    : 10/18/15
*/
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

extern FILE *yyin;

static struct {
    FILE *fp;
    char *name;
} infile[INPSTACKMAX];

static int ilevel, get_from_stdin;

PUBLIC void inilinebuffer(char *str)
{
    infile[0].fp = yyin;
    infile[0].name = str;
}

PUBLIC int doinclude(char *filnam)
{
    if (ilevel + 1 == INPSTACKMAX)
	execerror("fewer include files", "include");
    infile[ilevel].fp = yyin;
    if ((yyin = fopen(filnam, "r")) != 0) {
	infile[++ilevel].fp = yyin;
	infile[ilevel].name = filnam;
	return 1;
    }
    execerror("valid file name", "include");
    return 0;
}

PUBLIC void redirect(FILE * fp)
{
    if (infile[ilevel].fp != fp && !get_from_stdin) {
	get_from_stdin = fp == stdin;
	if (++ilevel == INPSTACKMAX)
	    execerror("fewer include files", "redirect");
	infile[ilevel].fp = fp;
	infile[ilevel].name = 0;
    }
}

int yywrap()
{
    if (--ilevel < 0)
	return 1;
    yyin = infile[ilevel].fp;
    return 0;
}
